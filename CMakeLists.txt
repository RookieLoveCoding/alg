cmake_minimum_required(VERSION 3.12)
project(HAL LANGUAGES C CXX)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置增量编译
option(ENABLE_INCR_COMPILE "Enable incremental compilation" ON)

# 设置一些关键变量
set(ROOT_PATH "${CMAKE_SOURCE_DIR}" CACHE STRING "the root path of project")

# 添加子目录
add_subdirectory(code)
add_subdirectory(infra)
add_subdirectory(command)
add_subdirectory(log)

# 合并库文件，统一对外发布
add_library(hal STATIC
    $<TARGET_OBJECTS:hal_api>
    $<TARGET_OBJECTS:stack>
    $<TARGET_OBJECTS:command>
    $<TARGET_OBJECTS:log>
    $<TARGET_OBJECTS:version>
    $<TARGET_OBJECTS:tool>
)

# 对外发布二进制和头文件
install(TARGETS hal
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/lib
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/lib
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/code/include/
        DESTINATION ${CMAKE_SOURCE_DIR}/output/${CHIP_TYPE}/release/include)
