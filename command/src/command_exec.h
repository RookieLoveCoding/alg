/*
 * 版权声明
 * @brief: 命令执行函数相关声明和结构
 * @author: liu
 * @date: 2025.12.24
 */

#ifndef COMMAND_EXEC_H
#define COMMAND_EXEC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CMD_DATANUM_MAX 8

typedef struct {
    double data[CMD_DATANUM_MAX]; /**< 用户输入的数据参数 */
    uint32_t inputDataNum; /**< 用户输入的数据参数个数 */
} CmdInput;

typedef uint32_t (*CmdExec)(CmdInput *input);
uint32_t cmdGetVersion(CmdInput *input);
uint32_t cmdDefaultExec(CmdInput *input);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* COMMAND_EXEC_H */