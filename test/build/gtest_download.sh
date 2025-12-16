#!/bin/bash

set -e

ROOT_PATH=".${pwd}/../.."
GTEST_VERSION="1.12.1"
GTEST_DIR="${ROOT_PATH}/third_party/googletest"

if [ ! -d "${GTEST_DIR}" ]; then
    echo "start downloading gtest ..."
    cd ${ROOT_PATH}/third_party/
    wget -q https://github.com/google/googletest/archive/refs/tags/release-${GTEST_VERSION}.tar.gz
    tar -xzf release-${GTEST_VERSION}.tar.gz
    mv googletest-release-${GTEST_VERSION} googletest
    rm release-${GTEST_VERSION}.tar.gz

    echo "google test download successs"
else
    echo "google test already exist"
fi

