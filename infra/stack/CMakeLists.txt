add_library(infra STATIC
    src/stack.c
)

target_include_directories(infra PUBLIC
    include/
)