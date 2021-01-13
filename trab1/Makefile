CC = gcc
EXEC = sc
SRC_DIR = src
SRCS =	$(SRC_DIR)/search.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/ls.c
INC_DIR = includes
FLAGS = -Wall -pedantic -lpthread -I $(INC_DIR) -D EXEC_NAME=$(EXEC)

all: build

debug: FLAGS += -g -D DEBUG
debug: build

test: FLAGS += -D TEST
test: build

build: $(SRCS)
	$(CC) $(SRCS) $(FLAGS) -o $(EXEC)
	chmod +x $(EXEC)

clean:
	rm $(EXEC)

valgrind:
	valgrind --log-file=valgrind_log --leak-check=yes ./$(EXEC) alloc -t 4
