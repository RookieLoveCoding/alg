/*
 * 版权声明
 * @brief: 命令树节点的执行函数实现
 * @author: liu
 * @date: 2025.12.24
 */

#include <stdio.h>
#include "command_exec.h"
#include "version.h"
#include "errcode.h"
#include "log.h"

uint32_t cmdGetVersion(CmdInput *input)
{
    printf("Current Version : %s\n", getVersion());
    printf("Version Date : %s\n", getDate());

    return HAL_OK;
}

uint32_t cmdDefaultExec(CmdInput *input)
{
    printf("this command is not support now\n");

    return HAL_OK;
}

uint32_t cmdHalSetLogLevel(CmdInput *input)
{
    uint32_t logLevel = (uint32_t)input->data[0];
    logSetLevel(HAL, logLevel);
    char *logLevelArr[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };
    printf("log level has been set to %s\n", logLevelArr[logLevel]);

    return HAL_OK;
}

uint32_t cmdHalSetLogOutput(CmdInput *input)
{
    bool logOutput = (bool)input->data[0];
    logSetOutput(HAL, logOutput);

    printf("log screen display has been set to %d\n", logOutput);

    return HAL_OK;
}

uint32_t cmdHalSetLogRotate(CmdInput *input)
{
    bool logRotate = (bool)input->data[0];
    logSetRotate(HAL, logRotate);

    printf("log rotate has been set to %d\n", logRotate);

    return HAL_OK;
}

uint32_t cmdGetHalLogConfig(CmdInput *input)
{
    LogConfig *config = logGetConfig(HAL);
    char *logLevelArr[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };

    printf("log level: %s\nlog file name: %s\nmax byte size: %d\nscreen output: %d\nrotate: %d\n",
            logLevelArr[config->logLevel], config->logFileName, config->maxByteSize,
            config->consoleOutput, config->rotate);

    return HAL_OK;
}