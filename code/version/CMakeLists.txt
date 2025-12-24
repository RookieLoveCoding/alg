add_library(version STATIC
    src/version.c
)

target_include_directories(version PUBLIC
    include/
)