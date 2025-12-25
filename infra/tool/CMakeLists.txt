add_library(tool STATIC
    src/tool.c
)

target_include_directories(tool PUBLIC
    include/
)