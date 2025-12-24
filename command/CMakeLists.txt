add_library(command STATIC

)

target_link_libraries(command PUBLIC
    version
)

target_include_directories(command PUBLIC
    include/
)