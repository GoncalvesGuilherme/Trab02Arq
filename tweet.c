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

	size += strlen(t->TEXT) * sizeof(char) + strlen(t->USER) * sizeof(char) + 
		strlen(t->COORDINATES) * sizeof(char) + strlen(t->LANGUAGE) * sizeof(char);
	printf("size %d\n", size);
	return size;
}

int createIndex(FILE *fp) {
	printf("creating index\n");
}

int addEnd(FILE *fp, TWEET *t, int totalSize, int *totalRegs) {
	char delimiter = '|';
	char text[strlen(t->TEXT)];
	char user[strlen(t->USER)];
	char coordinates[strlen(t->COORDINATES)];
	char language[strlen(t->LANGUAGE)];
	int favorite, retweet;
	long views;
	
	strcpy(text, t->TEXT);
	strcpy(user, t->USER);
	strcpy(coordinates, t->COORDINATES);
	strcpy(language, t->LANGUAGE);
	favorite = t->FAVORITE_COUNT;
	retweet = t->RETWEET_COUNT;
	views = t->VIEWS_COUNT;

	//rewind(fp);
	fseek(fp, 0, SEEK_END);

	fwrite(&totalSize, sizeof(int), 1, fp);
	fwrite(text, strlen(text), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(user, strlen(user), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(coordinates, strlen(coordinates), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(language, strlen(language), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(&favorite, sizeof(int), 1,fp);
	fwrite(&retweet, sizeof(int), 1, fp);
	fwrite(&views, sizeof(long), 1, fp);
	
	*totalRegs++;
	printf(".c72 totalRegs: %d\n", *totalRegs);
	if (*totalRegs == 10) {
		createIndex(fp);
	}

	return 0;
}

int addMiddle(FILE *fp, TWEET *t, int totalSize, int *totalRegs) {

}

int addTweet(FILE *fp, TWEET *newTweet, int *totalRegs) {
	int stackTop, totalSize;

	totalSize = calculatesTweetSize(newTweet);
	printf("totalSize: %d\n", totalSize);

	rewind(fp);
	//fseek(fp, sizeof(int), SEEK_SET);
	fread(&stackTop, sizeof(int), 1, fp);

	if (stackTop == -1) {
		return addEnd(fp, newTweet, totalSize, totalRegs);
	}
	else {
		return addMiddle(fp, newTweet, totalSize, totalRegs);
	}
}

char* alloc_str(int size) {
    char* str;

    str = (char *) malloc(size * sizeof(char));

    return str;
}

int readAllTweets(FILE* fd) {
    int length, i;
    char str[100], c;
    TWEET t;

    rewind(fd);
	fseek(fd, sizeof(int), SEEK_SET);

    while(1) {
        fread(&length, sizeof(int), 1, fd); // Ve o tamanho do proximo registro
        if(feof(fd)) {
            break;
        }
        
        i = 0;
        c = fgetc(fd);
        while (c != '|') {
        	str[i] = c;
        	i++;
        	c = fgetc(fd);
        }
        str[i] = '\0';
        t.TEXT = alloc_str(strlen(str));
        strcpy(t.TEXT, str);
        printf("text: %s\n", t.TEXT);
        
        i = 0;
        c = fgetc(fd);
        while (c != '|') {
        	str[i] = c;
        	i++;
        	c = fgetc(fd);
        }
        str[i] = '\0';
        t.USER = alloc_str(strlen(str));
        strcpy(t.USER, str);
        printf("user: %s\n", t.USER);
        
        i = 0;
        while((str[i] = fgetc(fd)) != '|') {
            i++;
        }
        str[i] = '\0';
        t.COORDINATES = alloc_str(strlen(str));
        strcpy(t.COORDINATES, str);
        printf("coordinates: %s\n", t.COORDINATES);
        i = 0;
        while((str[i] = fgetc(fd)) != '|') {
            i++;
        }
        str[i] = '\0';
        t.LANGUAGE = alloc_str(strlen(str));
        strcpy(t.LANGUAGE, str);
        printf("language: %s\n", t.LANGUAGE);
        fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
        printf("favorite:%d\n", t.FAVORITE_COUNT);
        fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
        printf("retweet: %d\n", t.RETWEET_COUNT);
        fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
        printf("views: %ld\n", t.VIEWS_COUNT);
    }
    return 0;
}
