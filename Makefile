all: tweet.o
	gcc -std=c99 -o main main.c tweet.c -Wall -g

tweet.o:
	gcc -std=c99 tweet.c

run:
	./main

clean:
	rm *.o main
