#!/bin/bash

chiptype=$1
if [ "${chiptype}" != "arm32" ] && [ "${chiptype}" != "arm64" ]; then
    sh help.sh
    exit 0
fi

# output/目录存放编译中间产物和日志等
if [ ! -d "../output/" ]; then
    mkdir -p "../output/"
fi

cd ../output/
# 清理历史编译中间件，保证每次编译都是全量编译
if [ -d "${chiptype}/" ]; then
    rm -rf ${chiptype}/
fi
mkdir -p ${chiptype}
cd ${chiptype}
cmake ../..
make
./myapp