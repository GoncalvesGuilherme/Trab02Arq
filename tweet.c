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

char* alloc_str(int size) {

    char* str;

    str = (char *) malloc(size * sizeof(char));

    return str;
}

void printTweet(TWEET t) {
    printf("\t\tTWEET:\n");
    printf("USER: %s\n", t.USER);
    printf("TEXT: %s\n", t.TEXT);
    printf("COORDINATES: %s\n", t.COORDINATES);
    printf("LANGUAGE: %s\n", t.LANGUAGE);
    printf("FAVORITE_COUNT: %d\n", t.FAVORITE_COUNT);
    printf("RETWEET_COUNT: %d\n", t.RETWEET_COUNT);
    printf("VIEWS_COUNT: %ld\n", t.VIEWS_COUNT);
}

int readAllTweets(FILE* fd) {

    int length, i = 0, j, k = 0;
    char str_aux[141];
    TWEET t;

    rewind(fd);

    fseek(fd, sizeof(int), SEEK_CUR);

    while(1) {
        //fread(&j, sizeof(int), 1, fd);
        fread(&length, sizeof(int), 1, fd); // Ve o tamanho do proximo registro
        if(feof(fd))
            break;
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '|') {
            i++;
        }
        str_aux[i] = '\0';
        printf("%s\n", str_aux);
        if(str_aux[0] != '*') {
            t.USER = alloc_str(strlen(str_aux));
            strcpy(t.USER, str_aux);
            //printf("%s\n", t.USER);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '|') {
                i++;
            }
            str_aux[i] = '\0';
            t.TEXT = alloc_str(strlen(str_aux));
            strcpy(t.TEXT, str_aux);
            //printf("%s\n", t.TEXT);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '|') {
                i++;
            }
            str_aux[i] = '\0';
            t.COORDINATES = alloc_str(strlen(str_aux));
            strcpy(t.COORDINATES, str_aux);
            //printf("%s\n", t.COORDINATES);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '|') {
                i++;
            }
            str_aux[i] = '\0';
            t.LANGUAGE = alloc_str(strlen(str_aux));
            strcpy(t.LANGUAGE, str_aux);
            //printf("%s\n", t.LANGUAGE);
            fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
            //printf("%d\n", t.FAVORITE_COUNT);
            fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
            //printf("%d\n", t.RETWEET_COUNT);
            fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
            //printf("%ld\n", t.VIEWS_COUNT);
            printTweet(t);
        }
        else {
            fseek(fd, length - (strlen(str_aux) + sizeof(int) + 1), SEEK_CUR);
        }
    }
    return 0;
}

int getTweetByUser(FILE* fd, char* user) {

    int length, i = 0, j;
    char str_aux[100];
    TWEET t;

    rewind(fd);

    fseek(fd, sizeof(int), SEEK_CUR);

    while(1) {
        //fread(&j, sizeof(int), 1, fd);
        fread(&length, sizeof(int), 1, fd);
        if(feof(fd))
            break;
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '|') {
            //printf("%c\n", str_aux[i]);
            i++;
        }
        printf("ftell antes do if: %d\n", (int)ftell(fd));
        //printf("%s\n", str_aux);
        //printf("%d %ld\n", (int)strlen(str_aux), ftell(fd));
        str_aux[i] = '\0';
        printf("%s\n", str_aux);
        if(strcmp(str_aux, user) == 0) {
            t.USER = alloc_str(strlen(str_aux));
            strcpy(t.USER, str_aux);
            //printf("%s\n", t.USER);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '|') {
                i++;
            }
            str_aux[i] = '\0';
            t.TEXT = alloc_str(strlen(str_aux));
            strcpy(t.TEXT, str_aux);
            //printf("%s\n", t.TEXT);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '|') {
                i++;
            }
            str_aux[i] = '\0';
            t.COORDINATES = alloc_str(strlen(str_aux));
            strcpy(t.COORDINATES, str_aux);
            //printf("%s\n", t.COORDINATES);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '|') {
                i++;
            }
            str_aux[i] = '\0';
            t.LANGUAGE = alloc_str(strlen(str_aux));
            strcpy(t.LANGUAGE, str_aux);
            //printf("%s\n", t.LANGUAGE);
            fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
            //printf("%d\n", t.FAVORITE_COUNT);
            fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
            //printf("%d\n", t.RETWEET_COUNT);
            fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
            //printf("%ld\n", t.VIEWS_COUNT);
            //printf("%ld\n", ftell(fd));
            printTweet(t);
        }
        else {
            fseek(fd, length - (strlen(str_aux) + sizeof(int)) + 4, SEEK_CUR);
        }
        //printf("ftell depois do if: %d\n", (int)ftell(fd));
    }
}

int calculatesTweetSize(TWEET *t) {
	int size;

	size = 2 * sizeof(int) + sizeof(long); // size somente dos int e do long, sem as strings

	size += strlen(t->TEXT) * sizeof(char) + strlen(t->USER) * sizeof(char) +
		strlen(t->COORDINATES) * sizeof(char) + strlen(t->LANGUAGE) * sizeof(char);
	//printf("size %d\n", size);
	return size;
}

/***** FUNCAO TESTE DO INDICE *****/

void testIndex(FILE *fd) {

    int favorite, i;

    rewind(fd);

    while(1) {
        fread(&favorite, sizeof(int), 1, fd);
        if(feof(fd))
            break;
        fread(&i, sizeof(int), 1, fd);
        printf("%d %d\n", favorite, i);
    }
}

/**********************************/

int compare(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}

int isInTheVector(sort_index *v, int n, int favorite) {
    int i;

    for(i = 0; i < n; i++) {
        if(v[i].FAVORITE_COUNT == favorite) {
            return 1;
        }
    }
    return 0;
}

int createIndex(FILE *fd) {
	printf("creating index\n");

    FILE *idx;
    int i = 0, j = 0, length, k, m = 0, offset;
    char str_aux[100];
    TWEET t;
    sort_index *vector = NULL;
    //vector = NULL;
    //vector = malloc(0);

    idx = fopen("idx.bin", "wb+");

    rewind(fd);

    while(1) {
        offset = ftell(fd);
        fseek(fd, sizeof(int), SEEK_CUR);
        fread(&length, sizeof(int), 1, fd);
        if(feof(fd))
            break;
        j = 0;
        while((str_aux[j] = fgetc(fd)) != '|') {
            j++;
        }
        str_aux[j] = '\0';
        j = 0;
        while((str_aux[j] = fgetc(fd)) != '|') {
            j++;
        }
        str_aux[j] = '\0';
        j = 0;
        while((str_aux[j] = fgetc(fd)) != '|') {
            j++;
        }
        str_aux[j] = '\0';
        j = 0;
        while((str_aux[j] = fgetc(fd)) != '|') {
            j++;
        }
        str_aux[j] = '\0';
        fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
        vector = (sort_index *) realloc(vector, (i+1) * sizeof(sort_index));
        if(isInTheVector(vector, m+1, t.FAVORITE_COUNT) == 0) {
            vector[m].FAVORITE_COUNT = t.FAVORITE_COUNT;
            vector[m].rrn = i;
            i++;
            m++;
        }
        //printf("%d %d\n", vector[m].FAVORITE_COUNT, vector[m].rrn);
        //fwrite(&t.FAVORITE_COUNT, sizeof(int), 1, idx);
        //fwrite(&i, sizeof(int), 1, idx);
        fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
        fread(&t.VIEWS_COUNT, sizeof(int), 1, fd);
    }

    int vector_length = m;

    printf("vector_length: %d\n", vector_length);

    qsort(vector, i, sizeof(sort_index), compare);

    for(k = 0; k < m; k++) {
        fwrite(&vector[k].FAVORITE_COUNT, sizeof(int), 1, idx);
        fwrite(&vector[k].rrn, sizeof(int), 1, idx);
        //printf("%d %d\n", vector[k].FAVORITE_COUNT, vector[k].rrn);
    }

    testIndex(idx);
    fclose(idx);
}

int addEnd(FILE *fp, TWEET *t, int totalSize, int *totalRegs) {
	char delimiter = '|';
	char text[strlen(t->TEXT)];
	char user[strlen(t->USER)];
	char coordinates[strlen(t->COORDINATES)];
	char language[strlen(t->LANGUAGE)];
	int favorite, retweet;
	long views;
    int x = 1;

	strcpy(text, t->TEXT);
	strcpy(user, t->USER);
	strcpy(coordinates, t->COORDINATES);
	strcpy(language, t->LANGUAGE);
	favorite = t->FAVORITE_COUNT;
	retweet = t->RETWEET_COUNT;
	views = t->VIEWS_COUNT;

	//rewind(fp);
	fseek(fp, 0, SEEK_END);

    //fwrite(&x, sizeof(int), 1, fp);
	fwrite(&totalSize, sizeof(int), 1, fp);
	fwrite(user, strlen(user), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(text, strlen(text), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(coordinates, strlen(coordinates), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(language, strlen(language), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(&favorite, sizeof(int), 1,fp);
	fwrite(&retweet, sizeof(int), 1, fp);
	fwrite(&views, sizeof(long), 1, fp);

	*totalRegs += 1;
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
	//printf("totalSize: %d\n", totalSize);
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

void write(FILE *fd) {
    int x = 61;
    int j = 4;
    char str[] = "Arnaldo|";
    char str2[] = "Isso eh um teste|";
    char str3[] = "3N24L|";
    char str4[] = "Portugues|";
    int y = 4;
    int z = 8;
    long a = 100;

    rewind(fd);

    fwrite(&j, sizeof(int), 1, fd);
    fwrite(&x, sizeof(int), 1, fd);
    fwrite(str, sizeof(char), strlen(str), fd);
    fwrite(str2, sizeof(char), strlen(str2), fd);
    fwrite(str3, sizeof(char), strlen(str3), fd);
    fwrite(str4, sizeof(char), strlen(str4), fd);
    fwrite(&y, sizeof(int), 1, fd);
    fwrite(&z, sizeof(int), 1, fd);
    fwrite(&a, sizeof(long), 1, fd);

    strcpy(str, "*ose|");
    strcpy(str2, "Teste profundo|");
    strcpy(str3, "24N24W|");
    strcpy(str4, "Ingles|");
    x = 54;
    y = 14;
    z = 18;
    a = 200;

    fwrite(&j, sizeof(int), 1, fd);
    fwrite(&x, sizeof(int), 1, fd);
    fwrite(str, sizeof(char), strlen(str), fd);
    fwrite(str2, sizeof(char), strlen(str2), fd);
    fwrite(str3, sizeof(char), strlen(str3), fd);
    fwrite(str4, sizeof(char), strlen(str4), fd);
    fwrite(&y, sizeof(int), 1, fd);
    fwrite(&z, sizeof(int), 1, fd);
    fwrite(&a, sizeof(long), 1, fd);

    strcpy(str, "Giovanna|");
    strcpy(str2, "Testeeeeeeee|");
    strcpy(str3, "11N11W|");
    strcpy(str4, "Frances|");
    x = 57;
    y = 65;
    z = 57;
    a = 2840;

    fwrite(&j, sizeof(int), 1, fd);
    fwrite(&x, sizeof(int), 1, fd);
    fwrite(str, sizeof(char), strlen(str), fd);
    fwrite(str2, sizeof(char), strlen(str2), fd);
    fwrite(str3, sizeof(char), strlen(str3), fd);
    fwrite(str4, sizeof(char), strlen(str4), fd);
    fwrite(&y, sizeof(int), 1, fd);
    fwrite(&z, sizeof(int), 1, fd);
    fwrite(&a, sizeof(long), 1, fd);
}