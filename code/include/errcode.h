/*
 * 版权声明
 * Description: 错误码集中定义
 * Author: liu
 * Date: 2025.12.15
 */

#ifndef ERRCODE_H
#define ERRCODE_H

#define HAL_OK 0

/* 这里只是举例，要根据实际业务来定义模块，如果业务复杂，也可以将错误码按比特位划分域段 */
typedef enum {
    HAL_COMMON = 0x10000000,
    HAL_BASE_SERVICE = 0x11000000,
    HAL_ALGORITHM = 0x12000000,
    HAL_MEMORY = 0x13000000,
    HAL_MODULE_MAX = 0x25000000
} halModule;

/* 可灵活扩展 */
typedef enum {
    HAL_INVALID_PARA = HAL_COMMON + 0x1,
    HAL_OUT_OF_MEMORY = HAL_COMMON + 0x2,
    HAL_NULLPTR = HAL_COMMON + 0x3,
    HAL_TIMEOUT = HAL_BASE_SERVICE + 0X1,
    HAL_INIT_FAIL = HAL_BASE_SERVICE + 0x2,

    HAL_ERRCODE_MAX = HAL_MODULE_MAX
} errCode;

#endif /* ERRCODE_H */