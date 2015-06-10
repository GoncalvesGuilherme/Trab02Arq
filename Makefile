all:
	@gcc -std=c99 -o main main.c tweet.c
run:
	@./main