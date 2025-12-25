/*
 * 版权声明
 * @brief: 命令树解析
 * @author: liu
 * @date: 2025.12.24
 */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "command_tree.h"

/* @brief 命令行解析函数 */
uint32_t cmdParse(char *usrInput)
{
    CmdNode *root = cmdGetRootNode();
    CmdNode *formerRoot = NULL;
    CmdInput input = { 0 };
    uint32_t usrInputIdx = 0;
    char *token = strtok(usrInput, " ");

    while (token != NULL) {
        /* 如果用户参数未解析完，但是命令树到子节点了，就执行default函数 */
        if (root->childNum == 0 || formerRoot == root) {
            return cmdDefaultExec(&input);
        }

        formerRoot = root;
        for (uint32_t i = 0; i < root->childNum; i++) {
            if (root->child[i].nodeType == STRING) {
                if (strcmp(root->child[i].nodeName, token) != 0) {
                    continue;
                }
                token = strtok(NULL, " ");
                root = &root->child[i];
                break;
            } else {
                input.data[input.inputDataNum++] = strtod(token, NULL);
                token = strtok(NULL, " ");
                root = &root->child[i];
                break;
            }
        }
    }

    return root->exec == NULL ? cmdDefaultExec(&input) : root->exec(&input);
}