CC = gcc
FLAGS = -Wall -pedantic -lpthread
EXEC = pi
SRCS = main.c safety.c

all: $(SRCS)
	$(CC) $(SRCS) $(FLAGS) -o $(EXEC)
	chmod +x $(EXEC)

clean:
	rm $(EXEC)
