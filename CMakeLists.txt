cmake_minimum_required(VERSION 3.10)
project(HAL)

add_subdirectory(code)
add_subdirectory(infra)

# 对外发布二进制和头文件
install(TARGETS hal_api
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/lib
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/lib
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/code/include/
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/${CHIP_TYPE}/release/include)
