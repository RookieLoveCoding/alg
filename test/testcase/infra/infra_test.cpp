#include <gtest/gtest.h>
#include "stack.h"
#include "errcode.h"

class InfraTest : public ::testing::Test {
    void SetUp() override {};
    void TearDown() override {};
};

Stack *g_newStack = (Stack *)malloc(sizeof(Stack));
TEST_F(InfraTest, WHEN_init_stack_SHOULD_return_OK)
{
    uint32_t stackSize = 5;
    int32_t ret = stackInit(g_newStack, stackSize);
    EXPECT_EQ(ret, HAL_OK);

    ret = stackPush(g_newStack, -5);
    EXPECT_EQ(ret, HAL_OK);
    ret = stackPush(g_newStack, 10);
    EXPECT_EQ(ret, HAL_OK);
    int32_t popNum = 0;
    ret = stackPop(g_newStack, &popNum);
    EXPECT_EQ(ret, HAL_OK);
    EXPECT_EQ(popNum, 10);
    ret = stackPop(g_newStack, &popNum);
    EXPECT_EQ(ret, HAL_OK);
    EXPECT_EQ(popNum, -5);

    stackDestory(g_newStack);
    EXPECT_EQ(g_newStack->stackMaxSize, 0);

    free(g_newStack);
}