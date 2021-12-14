# enum2s

## Dependencies

- libclang

``` shell
wget https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.0/clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz
tar xf clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz
ln -s clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04 enum2s/llvm
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
