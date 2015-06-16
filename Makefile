all:
	gcc -std=c99 -o main main.c tweet.c -Wall -g

clean:
	rm main *.bin

run:
	./main