#include <cstdint>

namespace test {
enum class Foo : uint32_t {
  a = 1,
  b,
  c,
};

enum struct Bar : uint32_t {
  a,
  b,
  c,
};

struct Baz {
  int a;
  bool b;
  char c;
};

enum {
  a,
  b,
  c,
};

}  // namespace test
