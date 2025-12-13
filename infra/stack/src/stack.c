/* 版权声明 */

#include <stddef.h>
#include <stdlib.h>
#include "stack.h"

/* 使用数组的方式实现栈要比链表形式更方便定位问题 */
int stackInit(Stack *stack, int stackSize)
{
    if (stackSize == 0 || stack == NULL) {
        return -1; /* TODO:这里应该返回规范的错误码 */
    }

    int *stackMem = (int *)malloc(stackSize * sizeof(int));
    stack->stackMemory = stackMem;
    stack->stackMaxSize = stackSize;
    stack->top = -1;

    return 0;
}

int stackPush(Stack *stack, int member)
{
    if (stack == NULL || (stack->top + 1) >= stack->stackMaxSize) {
        return -1;
    }

    stack->stackMemory[stack->top + 1] = member;
    stack->top++;

    return 0;
}

int stackPop(Stack *stack, int *value)
{
    if (stack == NULL || stack->top == -1) {
        return -1;
    }

    *value = stack->stackMemory[stack->top];
    stack->top--;

    return 0;
}

void stackDestory(Stack *stack)
{
    if (stack == NULL) {
        return;
    }

    (void)free(stack->stackMemory);
}