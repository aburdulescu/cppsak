#include <cassert>
#include <cstdio>
#include <cstring>

#include "input.hpp"

int main() {
  assert(strcmp(test::EnumName_Foo(static_cast<test::Foo>(0)), "") == 0);
  assert(strcmp(test::EnumName_Foo(test::Foo::a), "Foo::a") == 0);
  assert(strcmp(test::EnumName_Foo(test::Foo::b), "Foo::b") == 0);
  assert(strcmp(test::EnumName_Foo(test::Foo::c), "Foo::c") == 0);
  assert(strcmp(test::EnumName_Foo(static_cast<test::Foo>(4)), "") == 0);

  assert(strcmp(test::EnumName_Bar(static_cast<test::Bar>(-1)), "") == 0);
  assert(strcmp(test::EnumName_Bar(test::Bar::a), "Bar::a") == 0);
  assert(strcmp(test::EnumName_Bar(test::Bar::b), "Bar::b") == 0);
  assert(strcmp(test::EnumName_Bar(test::Bar::c), "Bar::c") == 0);
  assert(strcmp(test::EnumName_Bar(static_cast<test::Bar>(4)), "") == 0);

  return 0;
}
