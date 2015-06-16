all:
	gcc -std=c99 -o main main.c tweet.c -Wall

clean:
	rm main *.bin

run:
	./main