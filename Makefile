CC=gcc

all: 
	@$(CC) -o test.out src/*.c test.c -I./include -Wall
test:
	./test.out
clean:
	@rm -f *.out *.o
