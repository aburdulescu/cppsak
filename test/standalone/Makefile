CPPSAK_BIN = ./../../b/cppsak
OUT = test

all: run

build:
	$(CPPSAK_BIN) enums --namespace=test --include-guard=__FOO_BAR_HPP__ input.hpp Foo Bar > foobar.hpp
	c++ -g -fsanitize=address,undefined -O3 -Wall -Wextra -o $(OUT) main.cpp

run: build
	./$(OUT)

clean:
	rm -f foobar.hpp $(OUT)
