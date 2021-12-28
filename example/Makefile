all: run

build:
	./../b/enums input.hpp Foo Bar > foobar.hpp
	c++ -g -fsanitize=address,undefined -O3 -Wall -Wextra -o enums_example main.cpp

run: build
	./enums_example

clean:
	rm -f foobar.hpp enums_example
