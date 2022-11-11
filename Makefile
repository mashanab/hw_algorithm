TARGET=./main.o
SRC=main7.cpp

.PHONY: run clean

all: build run clean

build: ${TARGET}

clean:
	rm ${TARGET}

${TARGET}: ${SRC}
	g++ ${SRC} -o ${TARGET} -std=c++20

run: build
	${TARGET}