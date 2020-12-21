CC = gcc
FLAGS = -Wall -pedantic -lpthread -lm
EXEC = pi
SRCS = main.c

all: build

debug: FLAGS += -g
debug: build

build: $(SRCS)
	$(CC) $(SRCS) $(FLAGS) -o $(EXEC)
	chmod +x $(EXEC)

clean:
	rm $(EXEC)
