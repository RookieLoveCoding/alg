/*
 * 版权声明
 * @brief: 命令树相关声明和结构
 * @author: liu
 * @date: 2025.12.24
 */

#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include "command_exec.h"

#ifdef __cplusplus
extern "C" {
#endif

/* @brief 节点类型 */
typedef enum {
    STRING, /**< 字符串类型，一般是固定节点 */
    INTEGER, /**< 整型，一般是业务数据 */
    FLOAT, /**< 浮点型，一般是业务数据 */
    DOUBLE /**< 浮点型，一般是业务数据 */
} CmdNodeType;

typedef struct CmdNode CmdNode;
/* @brief 节点 */
struct CmdNode {
    CmdNodeType nodeType; /**< 节点类型 */
    char *nodeName; /**< 节点名称，只有当节点类型是STRING时才使用 */
    char *desc; /**< 节点描述信息 */
    uint32_t childNum; /**< 节点孩子数量 */
    CmdNode *child; /**< 节点孩子 */
    CmdExec exec; /**< 节点执行函数 */
};

CmdNode *cmdGetRootNode();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* COMMAND_TREE_H */