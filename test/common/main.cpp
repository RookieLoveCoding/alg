#include <stdio.h>
#include <gtest/gtest.h>
#include "stack.h"
#include "errcode.h"
#include "hal_api.h"
#include "command.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    printf("first line\n");

    uint32_t ret = halInit();
    if (ret != HAL_OK) {
        return HAL_INIT_FAIL;
    }

    char *runmode = argv[1];
    if (strcmp(runmode, "cmd") != 0) {
        return RUN_ALL_TESTS();
    }

    printf("------------------------------CMD MODE------------------------------------\n");
    while (1) {
        printf(">>");
        char input[128];
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n') {
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        cmdParse(input);
    }
    
    return HAL_OK;
}