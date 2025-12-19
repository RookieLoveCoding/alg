#!/bin/bash

chiptype=$1
buildtype="emu"
# 获取脚本所在目录的绝对路径
SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"
# 设置根目录为脚本目录的上两级
ROOT_PATH="$(dirname "$(dirname "${SCRIPT_DIR}")")"

if [ "${chiptype}" != "arm32" ] && [ "${chiptype}" != "arm64" ]; then
    echo "only sh build_emu.sh arm32/arm64 supported"
    exit 0
fi

# 创建临时目录存放编译中间产物和日志等
if [ ! -d "${chiptype}" ]; then
    mkdir -p "${chiptype}"
fi
cd ${chiptype}
rm -rf *

cd ${ROOT_PATH}/build
sh build.sh ${chiptype} ${buildtype}
cp ${ROOT_PATH}/output/${chiptype}/release/lib/*.a ${ROOT_PATH}/test/build/${chiptype}

cd ${ROOT_PATH}/test/build/${chiptype}
cmake ../.. -DCHIP_TYPE=${chiptype}
make -j16
./myapp