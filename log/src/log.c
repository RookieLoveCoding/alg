/*
 * 版权声明
 * @brief: log关键接口定义
 * @author: liu
 * @date: 2025.12.22
 */

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/time.h>
#include "log.h"
#include "errcode.h"

/* @note 日志名和组件名保持一致，禁止随意改动 */
static LogModule logModule[] = { HAL, FOS, NSE };
static const char* logName[] = { "hal.log", "fos.log", "nse.log" };
static char *logLevelName[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };
/* @note 把作用域限制在本文件，外部只能通过开放出的接口去访问和修改 */
static LogConfig* g_logConfig = NULL;

/* 
 * @brief 日志系统初始化，这里只用作仿真，因为正式版本中所有组件要统一
 * 使用一套日志文件管理，方便从设备导出日志。一般来说由上层提供日志初始化接口
 * 或注册接口或buffer指针更合适
 */
uint32_t logInit(LogLevel logLevel, uint32_t maxByteSize, bool rotate)
{
    if (g_logConfig == NULL) {
        g_logConfig = (LogConfig *)malloc(sizeof(LogConfig) * MODULE_MAX);
    }

    for (uint32_t i = 0; i < MODULE_MAX; i++) {
        /* 如果日志文件不存在会创建 */
        FILE *file = fopen(logName[i], "a");
        if (file == NULL) {
            logDestroy(); /* 释放已申请到的资源，避免泄露 */
            return HAL_OUT_OF_MEMORY;
        }

        strcpy(g_logConfig[i].logFileName, logName[i]);
        g_logConfig[i].file = file;
        g_logConfig[i].logModule = logModule[i];
        g_logConfig[i].logLevel = logLevel;
        g_logConfig[i].maxByteSize = maxByteSize;
        g_logConfig[i].rotate = rotate;
        g_logConfig[i].consoleOutput = true; /* 屏幕打印默认开启 */
        pthread_mutex_init(&g_logConfig[i].mutex.mutex, NULL);
        g_logConfig[i].mutex.isInited = true;

        fprintf(file, "=== Log initialized at %ld ===\n", (long)time(NULL));
        fflush(file);
    }

    return HAL_OK;
}

/* @brief 日志去初始化 */
void logDestroy()
{
    if (g_logConfig == NULL) {
        return;
    }

    for (uint32_t i = 0; i < MODULE_MAX; i++) {
        if (g_logConfig[i].file != NULL) {
            fclose(g_logConfig[i].file);
        }
        if (g_logConfig[i].mutex.isInited) {
            pthread_mutex_destroy(&g_logConfig[i].mutex.mutex);
            g_logConfig[i].mutex.isInited = false;
        }
    }
    free(g_logConfig);
    g_logConfig = NULL;
}

LogConfig *logGetConfig(LogModule module)
{
    if (g_logConfig == NULL || module == MODULE_MAX) {
        return NULL;
    }

    return &g_logConfig[module];
}

/* @brief 设置日志等级 */
void logSetLevel(LogModule module, LogLevel level)
{
    if (module == MODULE_MAX) {
        return;
    }

    pthread_mutex_lock(&g_logConfig[module].mutex.mutex);
    g_logConfig[module].logLevel = level;
    pthread_mutex_unlock(&g_logConfig[module].mutex.mutex);
}

/* @brief 设置日志是否屏幕输出 */
void logSetOutput(LogModule module, bool consoleOutput)
{
    if (module == MODULE_MAX) {
        return;
    }

    pthread_mutex_lock(&g_logConfig[module].mutex.mutex);
    g_logConfig[module].consoleOutput = consoleOutput;
    pthread_mutex_unlock(&g_logConfig[module].mutex.mutex);
}

/* @brief 设置日志是否循环覆盖 */
void logSetRotate(LogModule module, bool rotate)
{
    if (module == MODULE_MAX) {
        return;
    }

    pthread_mutex_lock(&g_logConfig[module].mutex.mutex);
    g_logConfig[module].rotate = rotate;
    pthread_mutex_unlock(&g_logConfig[module].mutex.mutex);
}

/* @brief 去掉路径，只保留文件名，以节省日志文件空间 */
const char *logGetBaseName(const char *path)
{
    const char *baseName = strrchr(path, '/'); /* 从右向左寻找第一个'/' */
    if (baseName != NULL) {
        return baseName + 1; /* 这里可以把文件名的部分字符替换为*，以提高系统安全性 */
    }

    return path;
}

/* @brief 获取系统时间，精确到毫秒 */
char *logGetTime()
{
    static char timeStr[64];
    struct timeval tv;
    time_t now = time(NULL);
    gettimeofday(&tv, NULL);
    struct tm *tmInfo = localtime(&now);
    size_t len = strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tmInfo);
    snprintf(timeStr + len, sizeof(timeStr) - len, ":%ld", tv.tv_usec / 1000); /* 纳秒转毫秒 */

    return timeStr;
}

/* @brief 检查日志是否写满，如果满了则循环覆盖 */
void logCheckRotate(LogConfig *config)
{
    /* 获取当前文件指针相较于起始位置的偏移字节数 */
    long fileSize = ftell(config->file);
    if (config->rotate && fileSize > config->maxByteSize) {
        rewind(config->file); /* 将文件指针位置切回文件起始位置 */
    }
}

/* @brief 日志写入 */
void logWrite(LogModule module, LogLevel level, const char *file, int32_t line, const char *format, ...)
{
    LogConfig *config = &g_logConfig[module];
    if (level < config->logLevel) {
        return; /* 等级低的日志不打印 */
    }

    pthread_mutex_lock(&config->mutex.mutex);
    logCheckRotate(config);
    int32_t len = snprintf(config->buffer, sizeof(config->buffer), "[%s][%s]%s:%d ",
                           logGetTime(), logLevelName[level], logGetBaseName(file), line);
    va_list args;
    va_start(args, format);
    vsnprintf(config->buffer + len, sizeof(config->buffer), format, args);
    va_end(args);

    fprintf(config->file, "%s", config->buffer);
    fflush(config->file);

    if (config->consoleOutput) {
        printf("%s\n", config->buffer);
    }
    /* 清空buffer */
    memset(config->buffer, '\0', sizeof(config->buffer));

    pthread_mutex_unlock(&config->mutex.mutex);
}