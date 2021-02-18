FLAGS = -Wall -pedantic -lpthread
THREADS = 1

all: build
all: test

debug: FLAGS += -g -DDEBUG
debug: build

build: qs.c qs.h
	gcc qs.c $(FLAGS) -o qs

.PHONY: test
test:
	./qs $(THREADS) < test
