all:
	@gcc -std=c99 -c main.c
	@gcc -std=c99 -c tweet.c
	@gcc main.o tweet.o -o program

run:
	@./program
