/**
 * Arnaldo Stanzani                  8937510
 * Guilherme Gonçalves               8937055
 * Guilherme Silva dos Anjos         8936830
 * Gustavo Henrique Oliveira Aguiar  8936912
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tweet.h"

int calculatesTweetSize(TWEET *t) {
	int size;

	size = 2 * sizeof(int) + sizeof(long); // size somente dos int e do long, sem as strings

	size = strlen(t->TEXT) * sizeof(char) + strlen(t->USER) * sizeof(char) + 
		strlen(t->COORDINATES) * sizeof(char) + strlen(t->LANGUAGE) * sizeof(char);

	return size;
}

int addEnd(FILE *fp, TWEET *t, int totalSize) {
	char delimiter = '|';

	fseek(fp, 0, SEEK_END);

	fwrite(&totalSize, sizeof(int), 1, fp);
	fwrite(&t->TEXT, sizeof(t->TEXT), 1, fp);
	fwrite(&delimiter, sizeof(delimiter), 1, fp);
	fwrite(&t->USER, sizeof(t->USER), 1, fp);
	fwrite(&delimiter, sizeof(delimiter), 1, fp);
	fwrite(&t->COORDINATES, sizeof(t->COORDINATES), 1, fp);
	fwrite(&delimiter, sizeof(delimiter), 1, fp);
	fwrite(&t->LANGUAGE, sizeof(t->LANGUAGE), 1, fp);
	fwrite(&delimiter, sizeof(delimiter), 1, fp);
	fwrite(&t->RETWEET_COUNT, sizeof(t->RETWEET_COUNT), 1, fp);
	fwrite(&t->VIEWS_COUNT, sizeof(t->VIEWS_COUNT), 1, fp);

	return 0;
}

int addMiddle(FILE *fp, TWEET *t, int totalSize) {

}

int addTweet(FILE *fp, TWEET *newTweet) {
	int stackTop, totalSize;

	totalSize = calculatesTweetSize(newTweet);

	fseek(fp, 0, SEEK_SET);
	fread(&stackTop, sizeof(int), 1, fp);

	if (stackTop == -1) {
		return addEnd(fp, newTweet, totalSize);
	}
	else {
		return addMiddle(fp, newTweet, totalSize);
	}
}
