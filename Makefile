CC=gcc

test: 
	@$(CC) -o test.out src/helperFunctions.c src/http_request_parser.c test.c -I./src
clean:
	@rm -f *.out *.o