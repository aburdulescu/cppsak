#include <cassert>
#include <cstdio>
#include <cstring>

#include "input.hpp"
#include "foobar.hpp"

int main() {
  assert(strcmp(test::EnumNameFoo(static_cast<test::Foo>(0)), "") == 0);
  assert(strcmp(test::EnumNameFoo(test::Foo::a), "a") == 0);
  assert(strcmp(test::EnumNameFoo(test::Foo::b), "b") == 0);
  assert(strcmp(test::EnumNameFoo(test::Foo::c), "c") == 0);
  assert(strcmp(test::EnumNameFoo(static_cast<test::Foo>(4)), "") == 0);

  assert(strcmp(test::EnumNameBar(static_cast<test::Bar>(-1)), "") == 0);
  assert(strcmp(test::EnumNameBar(test::Bar::a), "a") == 0);
  assert(strcmp(test::EnumNameBar(test::Bar::b), "b") == 0);
  assert(strcmp(test::EnumNameBar(test::Bar::c), "c") == 0);
  assert(strcmp(test::EnumNameBar(static_cast<test::Bar>(4)), "") == 0);

  return 0;
}
