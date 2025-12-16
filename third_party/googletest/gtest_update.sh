#!/bin/bash
# note :项目上各组件最好保持gtest版本一致，一般只有在项目统一更新gtest版本时才执行本脚本

# 创建临时文件夹，更新之后会直接删除
mkdir temp
cd temp

# 下载最新googletest源码
GTEST_VERSION="1.12.1"
GTEST_ARCHIVE="release-${GTEST_VERSION}.tar.gz"
GTEST_SRC_DIR="googletest-release-${GTEST_VERSION}"
echo "Downloading googletest source code ..."
wget https://github.com/google/googletest/archive/refs/tags/${GTEST_ARCHIVE}
tar -xzf ${GTEST_ARCHIVE}
echo "Download finish"

# 更新头文件
echo "Updating header files ..."
cd ..
rm -rf include/gtest/*
cp -r temp/${GTEST_SRC_DIR}/googletest/include/gtest/* include/gtest
rm -rf include/gmock/*
cp -r temp/${GTEST_SRC_DIR}/googlemock/include/gmock/* include/gmock
echo "Update header files finish"

# 更新二进制文件
echo "Start Building target ..."
cd temp/${GTEST_SRC_DIR}/
# 设置编译选项
local CMAKE_OPTION="-DCMAKE_BUILD_TYPE=Release \\
                    -DBUILD_GMOCK=ON -DINSTALL_GTEST=OFF \\
                    -Dgtest_build_tests=OFF -Dgmock_build_tests=OFF \\
                    -DBUILD_SHARED_LIBS=OFF"
# 一般gtest都于仿真验证，实际嵌入式设备上不会使用，所以这里只编译x86_64的二进制，不做交叉编译
mkdir linux-x86_64
cd linux-x86_64
cmake .. ${CMAKE_OPTION}
make -j16
echo "Build target finish"

echo "Start updating target ..."
cd ../../..
cp -f temp/${GTEST_SRC_DIR}/linux-x86_64/lib/* lib/linux-x86_64
echo "target update finish"

rm -rf temp
echo "gtest update finish"