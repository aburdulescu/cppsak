# enums

Generate code for pretty-printing C++ enums.

## Download

Go to the [latest]() release, download attached archive(`enums.gz`) and ungzip it.

Optionally, you can copy it somewhere in your `PATH`(e.g. `/usr/local/bin`).

If you want to build it from source follow [these](./doc/build_from_src.md) instructions.

## Usage

``` shell
enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
  --namespace=value      add given namespace to the generated file
  --include-guard=value  add given include guard to the generated file
```
