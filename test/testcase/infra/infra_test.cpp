#include <gtest/gtest.h>
#include "stack.h"
#include "errcode.h"

class StackTest : public ::testing::Test {
    public:
        static void SetUpTestSuite()
        {
            myStack = new Stack;
        }

        static void TearDownTestSuite()
        {
            delete myStack;
            myStack = nullptr;
        }

        void SetUp() override {};
        void TearDown() override {};

        static Stack *myStack;
        int32_t ret;
};
Stack *StackTest::myStack = nullptr;

TEST_F(StackTest, WHEN_init_stack_SHOULD_return_OK)
{
    uint32_t stackSize = 5;
    ret = stackInit(myStack, stackSize);
    EXPECT_EQ(ret, HAL_OK);
}

TEST_F(StackTest, WHEN_push_pop_SHOULD_return_OK)
{
    ret = stackPush(myStack, -5);
    EXPECT_EQ(ret, HAL_OK);
    ret = stackPush(myStack, 10);
    EXPECT_EQ(ret, HAL_OK);
    int32_t popNum = 0;
    ret = stackPop(myStack, &popNum);
    EXPECT_EQ(ret, HAL_OK);
    EXPECT_EQ(popNum, 10);
    ret = stackPop(myStack, &popNum);
    EXPECT_EQ(ret, HAL_OK);
    EXPECT_EQ(popNum, -5);
}

TEST_F(StackTest, WHEN_destroy_stack_SHOULD_return_OK)
{
    stackDestory(myStack);
    EXPECT_EQ(myStack->stackMaxSize, 0);
}