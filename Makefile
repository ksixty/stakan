CC ?= gcc-11

OBJECTS = $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

all: build/stakan

run: clean build/stakan
	build/stakan

build:
	mkdir -p build

clean:
	rm -rf build

build/stakan: $(OBJECTS)
	$(CC) -g -o $@ $^

build/%.o: src/%.c | build
	$(CC) -Og -c -std=c11 -o $@ $<
