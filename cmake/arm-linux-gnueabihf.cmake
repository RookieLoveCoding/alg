set(CMAKE_SYSTEM_NAME linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 指定交叉编译器
set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

# 验证编译器是否存在
execute_process(
    COMMAND ${CMAKE_C_COMPILER} --version
    OUTPUT_VARIABLE COMPILER_VERSION
    ERROR_VARIABLE COMPILER_ERROR
    RESULT_VARIABLE COMPILER_RESULT
)
if(NOT COMPILER_RESULT EQUAL 0)
    message(FATAL_ERROR "Cross-compiler not found: ${CMAKE_C_COMPILER}")
endif()

# 设置编译器标志
set(COMMON_FLAGS "-march=armv7-a -mfpu=neon-vfpv4 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -O2 -pipe" CACHE STRING "C Flags")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11" CACHE STRING "C++ Flags")

# 设置链接器标志
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-O1 -Wl,--as-needed" CACHE STRING "Executable linker flags")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-O1 -Wl,--as-needed" CACHE STRING "Shared library linker flags")
set(CMAKE_MODULE_LINKER_FLAGS "-Wl,-O1 -Wl,--as-needed" CACHE STRING "Module linker flags")
set(CMAKE_STATIC_LINKER_FLAGS "" CACHE STRING "Static library linker flags")

# 设置sysroot
if(DEFINED ENV{SYSROOT})
    set(SYSROOT_PATH $ENV{SYSROOT})
else()
    execute_process(COMMAND ${CMAKE_C_COMPILER} -print-sysroot
        OUTPUT_VARIABLE SYSROOT_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(NOT SYSROOT_PATH)
        set(SYSROOT_PATH /opt/arm-sysroot)
    endif()
endif()
set(CMAKE_SYSROOT ${SYSROOT_PATH})
set(CMAKE_FIND_ROOT_PATH ${SYSROOT_PATH})

# 设置搜索路径
set(CMAKE_FIND_ROOT_PATH /path/to/sysroot)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  # 不在sysroot中查找可执行文件
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)   # 只在sysroot中查找库
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)   # 只在sysroot中查找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)   # 只在sysroot中查找包
