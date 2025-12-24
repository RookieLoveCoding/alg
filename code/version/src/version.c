/*
 * 版权声明
 * @brief: 版本号相关实现
 * @author: liu
 * @date: 2025.12.24
 */

#include "version.h"

const char *getVersion()
{
    return HAL_VERSION;
}

const char *getDate()
{
    return HAL_VERSION_DATE;
}