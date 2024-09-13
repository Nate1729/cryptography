COMPILER_FLAGS=--std=c89 -Wall
COMPILER=gcc

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) $^ -c

affine: main.c affine_cipher.o cli_parser.o
	$(COMPILER) $(COMPILER_FLAGS) $^ -o $@

clean:
	rm *.o
