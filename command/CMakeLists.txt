add_library(command STATIC
    src/command_exec.c
    src/command_tree.c
    src/command.c
)

target_link_libraries(command PUBLIC
    version
    tool
)

target_include_directories(command PUBLIC
    include/
    ${ROOT_PATH}/code/include
)