# enums

Generate code for pretty-printing C++ enums.

## Usage

``` shell
Usage: cppsak enums [FLAGS] inputfile.[ch]pp enum_name1...enum_nameN

Flags:
    -h, --help             print this message
    --version              print version
    --namespace=value      add given namespace to the generated file
    --include-guard=value  add given include guard to the generated file
```

## Examples

Let's say you have the following header(`input.hpp`) which contains the enum `Foo`:

``` cpp
#include <cstdint>

namespace test {
enum class Foo : uint32_t {
  a = 1,
  b,
  c,
  d,
  e,
};
}  // namespace test
```

Now you want to be able to print the string equivalent for a given enum literal
for the `Foo` enum.

For `Foo::a` print `"a"`, for `Foo::b` print `"b"` and so on.

You can use the `cppsak enums` command to generate code that can be used to do exactly that.

There are two approaches:

### Generate the code and include it into the original header

Here's how:

- run the tool:

``` shell
cppsak enums --namespace=test input.hpp Foo > input_generated.inc
```

- include the generated code at the end of `input.hpp`:

``` cpp
#include <cstdint>

namespace test {
enum class Foo : uint32_t {
  a = 1,
  b,
  c,
};

#include "input_generated.inc"

}  // namespace test

```

Now, wherever you include the `input.hpp` header, you have access to the generated `EnumNameFoo()` function.

``` cpp
#include "input.hpp"

...

std::cout << EnumNameFoo(test::Foo::a) << std::endl;
```

This will print the string `"a"`.

### Generate the code as a standalone header

Here's how:

- run the tool:

``` shell
cppsak enums --namespace=test --include-guard=__INPUT_GENERATED_HPP__ input.hpp Foo > input_generated.hpp
```

Now, wherever you include the `input.hpp` header and
if after it you include the `input_generated.hpp` header,
you have access to the generated `EnumNameFoo()` function.

``` cpp
#include "input.hpp"
#include "input_generated.hpp"

...

std::cout << EnumNameFoo(test::Foo::a) << std::endl;
```

This will print the string `"a"`.
