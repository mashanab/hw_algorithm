TARGET=./main.o
SRC=main_4_3_queue_with_priority.cpp

.PHONY: run clean

all: build run clean

build: ${TARGET}

clean:
	rm ${TARGET}

${TARGET}: ${SRC}
	g++ ${SRC} -o ${TARGET} -std=c++20

run: build
	${TARGET}