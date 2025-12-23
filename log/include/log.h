/*
 * 版权声明
 * @brief: log关键结构和接口声明
 * @author: liu
 * @date: 2025.12.22
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE 512

/* @brief 日志等级 */
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

typedef enum {
    HAL = 0,
    FOS,
    NSE,
    MODULE_MAX
} LogModule;

typedef struct {
    pthread_mutex_t mutex; /**< 日志锁 */
    bool isInited; 
} LogSafeMutex; /**< 初始化状态 */

/* @brief 日志系统配置 */
typedef struct {
    LogModule logModule; /**< 日志所属组件 */
    LogLevel logLevel; /**< 开放的日志等级 */
    char logFileName[256]; /**< 日志文件名 */
    char buffer[BUFFER_SIZE]; /**< 缓冲区 */
    FILE *file; /**< 日志文件句柄 */
    uint32_t maxByteSize; /**< 日志文件最大字节数 */
    bool consoleOutput; /**< 是否输出到屏幕 */
    bool rotate; /**< 当日志文件满时是否循环覆盖 */
    LogSafeMutex mutex; /**< 日志锁 */
} LogConfig;

uint32_t logInit(LogLevel logLevel, uint32_t maxByteSize, bool rotate);
void logDestroy();
void logSetLevel(LogModule module, LogLevel logLevel);
void logSetOutput(LogModule module, bool consoleOutput);
void logSetRotate(LogModule module, bool rotate);
void logWrite(LogModule module, LogLevel level, const char *file, int32_t line, const char *format, ...);

#define HAL_LOG_DEBUG(...) logWrite(HAL, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__);
#define HAL_LOG_INFO(...) logWrite(HAL, LOG_INFO, __FILE__, __LINE__, __VA_ARGS__);
#define HAL_LOG_WARNING(...) logWrite(HAL, LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__);
#define HAL_LOG_ERROR(...) logWrite(HAL, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__);
#define HAL_LOG_FATAL(...) logWrite(HAL, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* LOG_H */