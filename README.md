# enums

Generate code for pretty-printing C++ enums.

## Supported platforms:

For now only `Linux x86/x86_64` systems are supported.

Other POSIX systems/CPU architectures may be added if needed.

For the missing platforms the tool can be compiled from source,
see [here](./doc/build_from_src.md).

## Download

Go to the [latest](https://github.com/aburdulescu/enums/releases/latest) release and:

- download the attached archive(for your CPU arch)
- download its corresponding SHA512 hash
- verify the hash: `sha512sum -c hash_file`. If this failed, stop and [submit an issue](https://github.com/aburdulescu/enums/issues/new).
- gunzip the archive

Optionally, if you want to install it, you can copy it somewhere in your `PATH`(e.g. `/usr/local/bin`).

## Usage

``` shell
enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
  --namespace=value      add given namespace to the generated file
  --include-guard=value  add given include guard to the generated file
```
