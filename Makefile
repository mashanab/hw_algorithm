TARGET=./main.o
SRC=main_3_btree.cpp

.PHONY: run clean

all: build run clean

build: ${TARGET}

clean:
	rm ${TARGET}

${TARGET}: ${SRC}
	g++ ${SRC} -o ${TARGET} -std=c++20 -g

run: build
	${TARGET}