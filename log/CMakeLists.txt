add_library(log STATIC
    src/log.c
)

target_include_directories(log PUBLIC
    include/
    ${ROOT_PATH}/code/include
)