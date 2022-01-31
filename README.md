# cppsak

C++ swiss army knife.

## Supported platforms

Only `Linux x86/x86_64` systems are supported.

For the missing platforms, the tool can be compiled from source.
See [here](./doc/build_from_src.md).

## Download

Go to the [latest](https://github.com/aburdulescu/cppsak/releases/latest) release and:

- download the attached gzipped file
- gunzip it
- make it executable: `chmod +x cppsak`

Optionally, if you want to install it, you can copy it somewhere in your `PATH`(e.g. `/usr/local/bin`).

## Usage

``` text
Usage: cppsak [COMMAND | FLAGS]

Commands:
    help    print this message or the one for the given command
    enums   generate code for pretty-printing enums
    gmocks  generate google mocks

Flags:
    -h, --help  print this message
    --version   print version

Run `cppsak help command` for more information about a specific command.
```

More info about the commands [here](./doc/usage.md).
