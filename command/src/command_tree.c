/*
 * 版权声明
 * @brief: 命令树结构
 * @author: liu
 * @date: 2025.12.24
 */

#include <stddef.h>
#include "command_tree.h"

CmdNode g_halChildNode[] = {
    {STRING, "version", NULL, halGetVersion},
};

CmdNode g_moduleNode[] = {
    {STRING, "hal", g_halChildNode, NULL},
    {STRING, "fos", NULL, NULL},
    {STRING, "nse", NULL, NULL},
};

CmdNode g_rootNode[] = {
    {STRING, "root", g_moduleNode, NULL},
};