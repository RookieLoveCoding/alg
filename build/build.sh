#!/bin/bash
# 整个项目的编译入口，发布件在output/${chiptype}/release目录

chiptype=$1
buildtype=$2 # 用来区分仿真和上板编译
if [ "${chiptype}" != "arm32" ] && [ "${chiptype}" != "arm64" ]; then
    sh help.sh
    exit 0
fi

# 获取脚本所在目录的绝对路径
SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"
ROOT_PATH="$(dirname "${SCRIPT_DIR}")"

# output/目录存放编译中间产物和日志等
if [ ! -d "../output/" ]; then
    mkdir -p "../output/"
fi

cd ../output/
# 清理残留，保证每次编译都是全量编译
if [ -d "${chiptype}/" ]; then
    rm -rf ${chiptype}
fi
mkdir -p ${chiptype}
cd ${chiptype}
if [ "${buildtype}" != "" ]; then
    cmake ../.. -DCHIP_TYPE=${chiptype}
else
    if [ "${chiptype}" = "arm32" ]; then
        cmake ../.. -DCHIP_TYPE=${chiptype} -DCMAKE_TOOLCHAIN_FILE=${ROOT_PATH}/cmake/arm-linux-gnueabihf.cmake
    else
        cmake ../.. -DCHIP_TYPE=${chiptype} -DCMAKE_TOOLCHAIN_FILE=${ROOT_PATH}/cmake/aarch64-linux-gnu-gcc.cmake
    fi
fi
make -j16
make install