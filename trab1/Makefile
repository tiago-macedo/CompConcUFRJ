CC = gcc
EXEC = sc
FLAGS += -D EXEC_NAME=$(EXEC)
SRC_DIR = src
SRCS =	$(SRC_DIR)/search.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/ls.c
INC_DIR = includes
FLAGS = -Wall -pedantic -lpthread -I $(INC_DIR)

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
