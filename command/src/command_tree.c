/*
 * 版权声明
 * @brief: 命令树结构
 * @author: liu
 * @date: 2025.12.24
 */

#include <stddef.h>
#include "command_tree.h"
#include "tool.h"

CmdNode g_halChildNode[] = {
    {STRING, "version", "显示版本号", 0, NULL, cmdGetVersion},
};

CmdNode g_moduleNode[] = {
    {STRING, "hal", "模块根节点", ARR_SIZE(g_halChildNode), g_halChildNode, NULL},
    {STRING, "fos", "模块根节点", 0, NULL, NULL},
    {STRING, "nse", "模块根节点", 0, NULL, NULL},
};

CmdNode g_rootNode[] = {
    {STRING, "root", "根节点", ARR_SIZE(g_moduleNode), g_moduleNode, NULL},
};

/* @brief 获取命令树根节点 */
CmdNode *cmdGetRootNode()
{
    return g_rootNode;
}