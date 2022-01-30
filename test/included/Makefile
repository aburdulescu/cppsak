CPPSAK_BIN = ./../../b/cppsak
OUT = test

all: run

build:
	$(CPPSAK_BIN) enums input.hpp Foo Bar > foobar.inc
	c++ -g -fsanitize=address,undefined -O3 -Wall -Wextra -o $(OUT) main.cpp

run: build
	./$(OUT)

clean:
	rm -f foobar.inc $(OUT)
