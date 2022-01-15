# enum2s

### Build

``` shell
./build.sh
```

### Install

Copy `b/enums` executable somewhere in your PATH(e.g. `/usr/local/bin`).

## Run

``` shell
enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
  --namespace=value      add given namespace to the generated file
  --include-guard=value  add given include guard to the generated file
```
