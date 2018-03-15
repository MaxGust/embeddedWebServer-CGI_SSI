CC=gcc

all: 
	@$(CC) -o test.out ./src/*.c ./test/*.c -I./test -I./include -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -std=c99 $(ENV) $(DEBUG)#-pedantic 
test:
	./test.out
clean:
	@rm -f *.out *.o
.PHONY: all test clean