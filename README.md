# enums

Generate code for pretty-printing C++ enums.

## Download

Go to the [latest]() release and:

- download the attached archive(for your CPU arch)
- download its corresponding SHA512 hash
- verify the hash: `sha512sum -c hash_file`. If this failed stop and [submit an issue]().
- ungzip the archive

Optionally, if you want to install it, you can copy it somewhere in your `PATH`(e.g. `/usr/local/bin`).

And that's it!

Note: If you want to build it from source follow [these](./doc/build_from_src.md) instructions.

## Usage

``` shell
enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
  --namespace=value      add given namespace to the generated file
  --include-guard=value  add given include guard to the generated file
```
