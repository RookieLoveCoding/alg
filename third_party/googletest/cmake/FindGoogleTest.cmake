# gtest/gmock查找

cmake_minimum_required(VERSION 3.10)

find_path(GTEST_INCLUDE_DIR
    NAMES gtest/gtest.h
    HINTS ${CMAKE_SOURCE_DIR}/../third_party/googletest/include
    NO_DEFAULT_PATH
)

find_path(GMOCK_INCLUDE_DIR
    NAMES gmock/gmock.h
    HINTS ${CMAKE_SOURCE_DIR}/../third_party/googletest/include
    NO_DEFAULT_PATH
)

set(LIB_SEARCH_PATHS
    ${CMAKE_SOURCE_DIR}/../third_party/googletest/lib/linux-x86_64
)

find_library(GTEST_LIBRARY
    NAMES gtest
    HINTS ${LIB_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

find_library(GTEST_MAIN_LIBRARY
    NAMES gtest_main
    HINTS ${LIB_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

find_library(GMOCK_LIBRARY
    NAMES gmock
    HINTS ${LIB_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

find_library(GMOCK_MAIN_LIBRARY
    NAMES gmock_main
    HINTS ${LIB_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

# 标准化处理
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GoogleTest
    REQUIRED_VARS 
        GTEST_INCLUDE_DIR
        GMOCK_INCLUDE_DIR
        GTEST_LIBRARY
        GTEST_MAIN_LIBRARY
        GMOCK_LIBRARY
        GMOCK_MAIN_LIBRARY
    VERSION_VAR
        GoogleTest_VERSION
)

# 如果找到，设置变量
if(GoogleTest_FOUND AND NOT TARGET GTest::gtest)
    # 设置包含目录变量
    set(GoogleTest_INCLUDE_DIRS 
        ${GTEST_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
    )
    
    # 设置库文件变量
    set(GoogleTest_LIBRARIES
        ${GTEST_LIBRARY}
        ${GTEST_MAIN_LIBRARY}
        ${GMOCK_LIBRARY}
        ${GMOCK_MAIN_LIBRARY}
    )
    
    # 创建导入目标（现代CMake方式）
    add_library(GTest::gtest STATIC IMPORTED)
    set_target_properties(GTest::gtest PROPERTIES
        IMPORTED_LOCATION "${GTEST_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIR}"
    )
    
    add_library(GTest::gtest_main STATIC IMPORTED)
    set_target_properties(GTest::gtest_main PROPERTIES
        IMPORTED_LOCATION "${GTEST_MAIN_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES GTest::gtest
    )
    
    add_library(GTest::gmock STATIC IMPORTED)
    set_target_properties(GTest::gmock PROPERTIES
        IMPORTED_LOCATION "${GMOCK_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES GTest::gtest
    )
    
    add_library(GTest::gmock_main STATIC IMPORTED)
    set_target_properties(GTest::gmock_main PROPERTIES
        IMPORTED_LOCATION "${GMOCK_MAIN_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES GTest::gmock
    )
endif()