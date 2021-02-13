FLAGS = -Wall -pedantic -lpthread

all: build
all: test

debug: FLAGS += -g -DDEBUG
debug: build

build: qs.c qs.h
	gcc qs.c $(FLAGS) -o qs

.PHONY: test
test:
	./qs < test
