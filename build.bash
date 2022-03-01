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

[[ $# -lt 1 ]] && echo "target was not provided" && exit 1

case $1 in
    "linux")
        zig_target=x86_64-linux-musl
        llvm_target=X86
        ;;
    "windows")
        zig_target=x86_64-windows-gnu
        llvm_target=X86
        ;;
    *)
        echo "unsupported target"
        exit 1
esac

export CC="zig cc -target $zig_target"
export CXX="zig c++ -target $zig_target"

cmake \
    -S . \
    -B $builddir \
    -G Ninja \
    -DENUMS_VERSION=$(cat version.txt) \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DLIBCLANG_BUILD_STATIC=ON \
    -DLLVM_ENABLE_PIC=OFF \
    -DLLVM_INCLUDE_BENCHMARKS=OFF \
    -DLLVM_TARGETS_TO_BUILD=$llvm_target

cmake --build $builddir --target libclang.a
cmake --build $builddir --target enums

strip b/enums
