/*
 * 版权声明
 * @brief: 命令行模块对外接口
 * @author: liu
 * @date: 2025.12.25
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t cmdParse(char *usrInput);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* COMMAND_H */