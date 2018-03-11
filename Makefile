CC=gcc

all: 
	@$(CC) -o test.out src/*.c test.c -I./include -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -std=c99 
pedantic:
	@$(CC) -o test.out src/*.c test.c -I./include -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -pedantic 
test:
	./test.out
clean:
	@rm -f *.out *.o
