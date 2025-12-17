cmake_minimum_required(VERSION 3.12)
project(MyApp)

# 使能测试
enable_testing()

set(TEST_FILES
    ${CMAKE_SOURCE_DIR}/testcase/infra/infra_test.cpp
)
add_executable(myapp common/main.cpp ${TEST_FILES})
target_link_libraries(myapp PUBLIC
    ${CMAKE_SOURCE_DIR}/build/${CHIP_TYPE}/libhal.a
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

    target_link_libraries(myapp PUBLIC
        GTest::gtest
        GMock::gmock
    )
    target_include_directories(myapp PUBLIC
        ${GoogleTest_INCLUDE_DIRS}
    )
else()
    message(FATAL_ERROR "GoogleTest not found")
endif()
