/*
 * 版权声明
 * @brief: 版本号相关声明
 * @author: liu
 * @date: 2025.12.24
 */

#ifndef VERSION_H
#define VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/* 每次发版本之前要修改 */
#define HAL_VERSION "V001"
#define HAL_VERSION_DATE "2025.12.24 14:25"

const char *getVersion();
const char *getDate();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* VERSION_H */