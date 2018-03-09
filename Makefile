CC=gcc

test: 
	@$(CC) -o test.out src/*.c test.c -I./include
clean:
	@rm -f *.out *.o
