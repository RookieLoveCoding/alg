add_library(hal_api STATIC
    src/hal_api.c
)

target_link_libraries(hal_api PUBLIC
    stack
    log
    version
)
target_include_directories(hal_api PUBLIC
    include
    ${ROOT_PATH}/code/include
)