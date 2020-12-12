CC = gcc
FLAGS = -Wall -pedantic
DEBUG_FLAGS = -g
PROD_FLAGS = -O3
EXEC = matrix

all: FLAGS += $(PROD_FLAGS)
all: build

debug: FLAGS += $(DEBUG_FLAGS)
debug: build

build: matrix.c
	$(CC) matrix.c $(FLAGS) -o $(EXEC)
	chmod +x $(EXEC)

clean:
	rm $(EXEC)
