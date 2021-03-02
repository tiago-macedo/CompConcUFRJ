FLAGS = -Wall -pedantic -lpthread

all: build
all: test

debug: FLAGS += -g -DDEBUG
debug: build
	@echo "======= debug ======="
	@./p < test

build: padroes.c
	gcc padroes.c $(FLAGS) -o p

gerateste: gerateste.c
	gcc gerateste.c -o gera

geramanual: geramanual.c
	gcc geramanual.c -o gera

.PHONY: test
test:
	@echo "====================="
	@./p < test
