# enum2s

## Install dependencies

### libclang

- via package manager(e.g. Deabian)

``` shell
sudo apt install libclang-dev
```

- download precompiled lib from LLVM release page

``` shell
wget https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.0/clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz
tar xf clang+llvm-13.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz -C /usr/local/ --strip 1
```

## Build and install

``` shell
cmake -S . -B b
cmake --build b
sudo cmake --build b --target install
```

## Run

``` shell
enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
  --namespace=value      add given namespace to the generated file
  --include-guard=value  add given include guard to the generated file
```
