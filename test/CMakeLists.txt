cmake_minimum_required(VERSION 3.10)
project(MyApp)

add_executable(myapp common/main.c)
target_link_libraries(myapp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/build/${CHIP_TYPE}/libhal_api.a
)
target_include_directories(myapp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../code/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../infra/stack/include
)
