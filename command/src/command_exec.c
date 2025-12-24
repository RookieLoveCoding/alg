/*
 * 版权声明
 * @brief: 命令树节点的执行函数实现
 * @author: liu
 * @date: 2025.12.24
 */

#include "command_exec.h"
#include "version.h"
#include "errcode.h"

uint32_t halGetVersion(CmdInput *input)
{
    printf("Current Version : %s\n", getVersion());
    printf("Version Date : $s\n", getDate());

    return HAL_OK;
}

uint32_t halDefaultExec(CmdInput *input)
{
    printf("this command is not support now\n");

    return HAL_OK;
}