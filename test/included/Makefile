ENUMS_BIN = ./../../b/enums
OUT = test

all: run

build:
	$(ENUMS_BIN) input.hpp Foo Bar > foobar.inc
	c++ -g -fsanitize=address,undefined -O3 -Wall -Wextra -o $(OUT) main.cpp

run: build
	./$(OUT)

clean:
	rm -f foobar.inc $(OUT)
