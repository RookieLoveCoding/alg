/*
 * 版权声明
 * @brief: 命令树结构
 * @author: liu
 * @date: 2025.12.24
 */

#include <stddef.h>
#include "command_tree.h"
#include "tool.h"

CmdNode g_halDisplayNode[] = {
    {STRING, "version", "显示版本号", 0, NULL, cmdGetVersion},
    {STRING, "logconfig", "显示日志配置信息", 0, NULL, cmdGetHalLogConfig},
};

CmdNode g_halLogLevelNode[] = {
    {INTEGER, "Input log level", "DEBUG:0, INFO:1, WARNING:2, ERROR:3, FATAL:4", 0, NULL, cmdHalSetLogLevel},
};

CmdNode g_halLogOutputNode[] = {
    {INTEGER, "Input screen display selection", "true:1, false:0", 0, NULL, cmdHalSetLogOutput},
};

CmdNode g_halLogRotateNode[] = {
    {INTEGER, "Input rotate selection", "true:1, false:0", 0, NULL, cmdHalSetLogRotate},
};

CmdNode g_halLogNode[] = {
    {STRING, "level", "设置日志等级", ARR_SIZE(g_halLogLevelNode), g_halLogLevelNode, NULL},
    {STRING, "output", "设置是否屏幕输出", ARR_SIZE(g_halLogOutputNode), g_halLogOutputNode, NULL},
    {STRING, "rotate", "设置日志是否循环覆盖", ARR_SIZE(g_halLogRotateNode), g_halLogRotateNode, NULL},
};

CmdNode g_halSetNode[] = {
    {STRING, "log", "日志系统相关设置", ARR_SIZE(g_halLogNode), g_halLogNode, NULL}
};

CmdNode g_halChildNode[] = {
    {STRING, "display", "查询&显示", ARR_SIZE(g_halDisplayNode), g_halDisplayNode, NULL},
    {STRING, "set", "配置", ARR_SIZE(g_halSetNode), g_halSetNode, NULL}
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