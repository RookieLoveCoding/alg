#!/bin/bash

# 检查Doxygen是否已安装
if dpkg -s doxygen &> /dev/null; then
    echo "Doxygen is installed."
else
    echo "Doxygen is not installed."
    echo "Start installing Doxygen ..."
    sudo apt-get install doxygen doxygen-gui
    echo "doxygen install finish"
fi

# 生成文档
doxygen Doxyfile
