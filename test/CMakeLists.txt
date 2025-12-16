cmake_minimum_required(VERSION 3.10)
project(MyApp)

add_executable(myapp common/main.c)
target_link_libraries(myapp PRIVATE
    ${CMAKE_SOURCE_DIR}/build/${CHIP_TYPE}/libhal_api.a
)
target_include_directories(myapp PUBLIC
    ${CMAKE_SOURCE_DIR}/../code/include
    ${CMAKE_SOURCE_DIR}/../infra/stack/include
)

set(GOOGLETEST_ROOT ${CMAKE_SOURCE_DIR}/../third_party/googletest)
list(APPEND CMAKE_MODULE_PATH ${GOOGLETEST_ROOT}/cmake)
find_package(GoogleTest REQUIRED)
if(GoogleTest_FOUND)
    message(STATUS "Found GoogleTest: ${GoogleTest_INCLUDE_DIRS}")
    message(STATUS "Found Libraries: ${GoogleTest_LIBRARIES}")

    target_link_libraries(myapp PRIVATE
        GTest::gtest
        GTest::gmock
    )
    target_include_directories(myapp PUBLIC
        ${GoogleTest_INCLUDE_DIRS}
    )
else()
    message(FATAL_ERROR "GoogleTest not found")
endif()
