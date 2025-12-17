add_library(stack STATIC
    src/stack.c
)

target_include_directories(stack PUBLIC
    include/
    ${ROOT_PATH}/code/include
)