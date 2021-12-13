# enum2s

## Dependencies

- libclang

``` shell
git clone --depth=1 https://github.com/llvm/llvm-project.git

mkdir llvm-build && cd llvm-build

cmake -DLLVM_ENABLE_PROJECTS=clang -G Ninja -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache ../llvm-project/llvm -DCMAKE_INSTALL_PREFIX=$(pwd)/../llvm-dst/ -DLIBCLANG_BUILD_STATIC=ON

ninja libclang

ninja install-libclang-stripped
ninja install-libclang-headers-stripped
```

## Usage

### Build
``` shell
cmake -S . -B b
cmake --build b
```

### Run

``` shell
./b/enum2s inputfile.[ch]pp enum_name1...enum_nameN
```
