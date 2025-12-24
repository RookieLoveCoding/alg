#include <stdio.h>
#include <gtest/gtest.h>
#include "stack.h"
#include "errcode.h"
#include "hal_api.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    printf("first line\n");

    uint32_t ret = halInit();
    if (ret != HAL_OK) {
        return HAL_INIT_FAIL;
    }

    return RUN_ALL_TESTS();
}