#!/bin/bash

set -e

llvm_version=13.0.0
builddir=b

if [[ ! -L "llvm-project" ]]
then
    wget https://github.com/llvm/llvm-project/releases/download/llvmorg-$llvm_version/llvm-project-$llvm_version.src.tar.xz
    tar xf llvm-project-$llvm_version.src.tar.xz
    ln -s llvm-project-$llvm_version.src llvm-project
fi

rm -rf $builddir

export CCACHE_DIR=/ccache

cmake \
    -S . \
    -B $builddir \
    -G Ninja \
    -DCPPSAK_VERSION=$(cat version.txt) \
    -DLIBCLANG_BUILD_STATIC=ON \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DLLVM_ENABLE_PIC=OFF \
    -DLLVM_TARGETS_TO_BUILD=X86

cmake --build $builddir --target libclang.a
cmake --build $builddir --target cppsak
cmake --build $builddir --target compdb_test

strip b/cppsak
