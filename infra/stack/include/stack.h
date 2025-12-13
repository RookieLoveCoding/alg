/* 版权声明 */

#ifndef STACK_INCLUDE_STACK_H
#define STACK_INCLUDE_STACK_H

#include <stdint.h>

typedef struct {
    int *stackMemory;
    int stackMaxSize;
    int top;
} Stack;

int stackInit(Stack *stack, int stackSize);
int stackPush(Stack *stack, int member);
int stackPop(Stack *stack, int *value);
void stackDestory(Stack *stack);

#endif /* STACK_INCLUDE_STACK_H */