/*
 * 版权声明
 * @brief: API实现
 * @author: liu
 * @date: 2025.12.15
 */

#include <stdio.h>
#include "hal_api.h"
#include "stack.h"
#include "errcode.h"
#include "log.h"
#include "version.h"

uint32_t halInit(void)
{
    uint32_t ret = logInit(LOG_DEBUG, 10 * 1024 * 1024, false);
    if (ret != HAL_OK) {
        printf("log init failed\n");
        return ret;
    }
    HAL_LOG_INFO("log init success\n");

    HAL_LOG_INFO("hal init finish\n");
    HAL_LOG_DEBUG("Current Version : %s\n", getVersion());
    HAL_LOG_DEBUG("Build Time : %s\n", getDate());

    return HAL_OK;
}
