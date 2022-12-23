TARGET=build/hw

.PHONY: run clean

all: build run clean

build: ${TARGET}

clean:
	rm -rf build

${TARGET}:
	scripts/build.sh

run: build
	./${TARGET}