#include <stdio.h>
#include <gtest/gtest.h>
#include "stack.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    printf("first line\n");

    return RUN_ALL_TESTS();
}