COMPILER_FLAGS=--std=c89 -Wall
COMPILER=gcc

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) $^ -c

caesar: main.c cli_parser.o caesar.o
	$(COMPILER) $(COMPILER_FLAGS) $^ -o $@

clean:
	rm *.o
