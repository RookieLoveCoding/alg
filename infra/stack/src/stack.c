/* 版权声明 */

#include <stddef.h>
#include <stdlib.h>
#include "stack.h"
#include "errcode.h"

/* 使用数组的方式实现栈要比链表形式更方便定位问题 */
int32_t stackInit(Stack *stack, uint32_t stackSize)
{
    if (stackSize == 0 || stack == NULL) {
        return HAL_INVALID_PARA;
    }

    int32_t *stackMem = (int32_t *)malloc(stackSize * sizeof(int32_t));
    stack->stackMemory = stackMem;
    stack->stackMaxSize = stackSize;
    stack->top = -1;

    return HAL_OK;
}

int32_t stackPush(Stack *stack, int32_t member)
{
    if (stack == NULL || (stack->top + 1) >= stack->stackMaxSize) {
        return HAL_INVALID_PARA;
    }

    stack->stackMemory[stack->top + 1] = member;
    stack->top++;

    return HAL_OK;
}

int32_t stackPop(Stack *stack, int32_t *value)
{
    if (stack == NULL || stack->top == -1) {
        return HAL_INVALID_PARA;
    }

    *value = stack->stackMemory[stack->top];
    stack->top--;

    return HAL_OK;
}

void stackDestory(Stack *stack)
{
    if (stack == NULL) {
        return;
    }

    free(stack->stackMemory);
    stack->stackMemory = NULL;
    stack->top = -1;
    stack->stackMaxSize = 0;
}