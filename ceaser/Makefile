COMPILER_FLAGS=--std=c89 -Wall
COMPILER=gcc

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) $^ -c

ceaser: main.c cli_parser.o
	$(COMPILER) $(COMPILER_FLAGS) $^ -o $@
