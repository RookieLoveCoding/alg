/* 版权声明 */

#ifndef STACK_INCLUDE_STACK_H
#define STACK_INCLUDE_STACK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int32_t *stackMemory;
    uint32_t stackMaxSize;
    int32_t top;
} Stack;

int32_t stackInit(Stack *stack, uint32_t stackSize);
int32_t stackPush(Stack *stack, int32_t member);
int32_t stackPop(Stack *stack, int32_t *value);
void stackDestory(Stack *stack);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* STACK_INCLUDE_STACK_H */