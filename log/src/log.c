/*
 * 版权声明
 * @brief: log关键接口定义
 * @author: liu
 * @date: 2025.12.22
 */

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"
#include "errcode.h"

/* @note 日志名和组件名保持一致，禁止随意改动 */
static LogModule logModule[] = { HAL, FOS, NSE };
static const char* logName[] = { "hal.log", "fos.log", "nse.log" };
/* @note 把作用域限制在本文件，外部只能通过开放出的接口去访问和修改 */
static LogConfig* g_logConfig = NULL;

/* 
 * @brief 日志系统初始化，这里只用作仿真，因为正式版本中所有组件要统一
 * 使用一套日志文件管理，方便从设备导出日志。一般来说由上层提供日志初始化接口
 * 或注册接口或buffer指针更合适
 */
uint32_t logInit(LogLevel logLevel, uint32_t maxByteSize, bool rotate)
{
    g_logConfig = (LogConfig *)malloc(sizeof(LogConfig) * MODULE_MAX);

    for (uint32_t i = 0; i < MODULE_MAX; i++) {
        /* 如果日志文件不存在会创建 */
        FILE *file = fopen(logName[i], "a");
        if (file == NULL) {
            /* TODO:这里要释放前面已经申请到的资源 */
            return HAL_OUT_OF_MEMORY;
        }

        strcpy(g_logConfig[i].logFileName, logName[i]);
        g_logConfig[i].file = file;
        g_logConfig[i].logModule = logModule[i];
        g_logConfig[i].logLevel = logLevel;
        g_logConfig[i].maxByteSize = maxByteSize;
        g_logConfig[i].rotate = rotate;
        g_logConfig[i].consoleOutput = false; /* 屏幕打印默认关闭 */
        pthread_mutex_init(&g_logConfig[i].mutex, NULL);

        fprintf(file, "=== Log initialized at %ld ===\n", (long)time(NULL));
        fflush(file);
    }

    return HAL_OK;
}

void logDestroy()
{
    for (uint32_t i = 0; i < MODULE_MAX; i++) {
        pthread_mutex_destroy(&g_logConfig[i].mutex);
    }
    free(g_logConfig);
}

void logSetLevel(LogModule module, LogLevel level)
{
    if (module == MODULE_MAX) {
        return;
    }

    pthread_mutex_lock(&g_logConfig[module].mutex);
    g_logConfig[module].logLevel = level;
    pthread_mutex_unlock(&g_logConfig[module].mutex);
}

void logSetOutput(LogModule module, bool consoleOutput)
{
    if (module == MODULE_MAX) {
        return;
    }

    pthread_mutex_lock(&g_logConfig[module].mutex);
    g_logConfig[module].consoleOutput = consoleOutput;
    pthread_mutex_unlock(&g_logConfig[module].mutex);
}

void logSetRotate(LogModule module, bool rotate)
{
    if (module == MODULE_MAX) {
        return;
    }

    pthread_mutex_lock(&g_logConfig[module].mutex);
    g_logConfig[module].rotate = rotate;
    pthread_mutex_unlock(&g_logConfig[module].mutex);
}

void logWrite(LogModule module, LogLevel level, const char *file, int32_t line, const char *format, ...)
{
    LogConfig *config = &g_logConfig[module];
    if (level < config->logLevel) {
        return; /* 等级低的日志不打印 */
    }

    pthread_mutex_lock(&config->mutex);
    int32_t len = snprintf(config->buffer, sizeof(config->buffer), "%s:%d ", file, line);
    va_list args;
    va_start(args, format);
    vsnprintf(config->buffer + len, sizeof(config->buffer), format, args);
    va_end(args);

    fprintf(config->file, "%s\n", config->buffer);
    fflush(config->file);
    /* 清空buffer */
    memset(config->buffer, '\0', sizeof(config->buffer));

    pthread_mutex_unlock(&config->mutex);
}