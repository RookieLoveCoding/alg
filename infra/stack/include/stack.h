/* 版权声明 */

#ifndef STACK_INCLUDE_STACK_H
#define STACK_INCLUDE_STACK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int *stackMemory;
    int stackMaxSize;
    int top;
} Stack;

int stackInit(Stack *stack, int stackSize);
int stackPush(Stack *stack, int member);
int stackPop(Stack *stack, int *value);
void stackDestory(Stack *stack);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* STACK_INCLUDE_STACK_H */