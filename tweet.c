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
            fseek(fd, length - (i+1), SEEK_CUR);
        }
    }
    return 0;
}

int removeTweet(FILE *fd, int favorite)
{
	TweetList* l, aux;
	TWEET t;
	char str_aux[141];
	char logicremove = '*';
	int i = 1, j, opc = INT_MAX, sp;
	fclose(fd);
	fd = fopen("data.bin", "rb+");
	l = getTweetByFavorite(fd, favorite);
	aux = l;
	while(l != NULL)
	{
		fseek(fd, l->offset + sizeof(int), SEEK_SET);
		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.USER = alloc_str(strlen(str_aux));
        strcpy(t.USER, str_aux);

		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.TEXT = alloc_str(strlen(str_aux));
        strcpy(t.TEXT, str_aux);

		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.COORDINATES = alloc_str(strlen(str_aux));
        strcpy(t.COORDINATES, str_aux);

		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.LANGUAGE = alloc_str(strlen(str_aux));
        strcpy(t.LANGUAGE, str_aux);

		fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
        fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
        fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
		printf("%d-\n", i);
		printTweet(t);
		l = l->nextNode;
		i++;
	}
	while(opc > (i - 1))
	{
		printf("Selecione o tweet que voce deseja apagar digitando o numero correspondente a ele: \n");
		scanf("%d", &opc);
	}
	for(i = 1; i < opc; i++)
		aux = aux->nextNode;
	rewind(fd);
	fread(&sp, sizeof(int), 1, fd);
	fseek(fd, aux->offset + sizeof(int), SEEK_SET);
	fwrite(&logicremove, sizeof(char), 1, fd);
	fwrite(&sp, sizeof(int), 1, fd);
	rewind(fd);
	fwrite(&aux->offset, sizeof(int), 1, fd);
	fclose(fd);
	fd = fopen("data.bin", "ab+");
	createIndex(fd);
	return 0;
}

TweetList* getTweetByFavorite(FILE* fd, int favorite)
{
	TweetList* aux, aux2, first = NULL;
	sort_indexfav fav;
	FILE* list;
	list = fopen("listFav.bin", "ab+");
	while(!feof)
	{
		fread(&fav, sizeof(sort_indexfav), 1, fd);
		if(fav.FAVORITE_COUNT == favorite)
		{
			fseek(list, fav.rrn, SEEK_SET);
			fread(&fav, sizeof(sort_indexfav), 1, list);
			if(first == NULL)
			{
				first = (TweetList *) malloc(sizeof(TweetList));
				first->offset = fav.offset;
				first->next = NULL;
				aux = first;
			}
			else
			{
				aux2 = (TweetList *) malloc(sizeof(TweetList));
				aux2->offset = fav.offset;
				aux2->next = NULL;
				aux->next = aux2;
				aux = aux2;
			}
		}
	}
	return first;
}

int getTweetByUser(FILE* fd, char* user) {

    int length, i = 0, j;
    char str_aux[141];
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
        //printf("ftell antes do if: %d\n", (int)ftell(fd));
        //printf("%s\n", str_aux);
        //printf("%d %ld\n", (int)strlen(str_aux), ftell(fd));
        str_aux[i] = '\0';
        //printf("%s\n", str_aux);
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
            fseek(fd, length - (i+1), SEEK_CUR);
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

void testIndex(FILE *fd, FILE *fd2) {
    int favorite, i, j;
	char language[20];
    rewind(fd);
	rewind(fd2);

    while(1) {
        fread(&favorite, sizeof(int), 1, fd);
		fread(&language, sizeof(char), 20, fd2);
        if(feof(fd))
            break;
        fread(&i, sizeof(int), 1, fd);
		fread(&j, sizeof(int), 1, fd2);
        printf("%d %d\n", favorite, i);
		printf("%s %d\n", language, i);
    }
}

/**********************************/

int compare(const void *a, const void *b) {
    return ((*(sort_indexfav*)a).FAVORITE_COUNT - (*(sort_indexfav*)b).FAVORITE_COUNT);
}

int comparelang(const void *a, const void *b) {
	char* str1 = (*(sort_indexlang *)a).language;
	char* str2 = (*(sort_indexlang *)b).language;
	int ret = strcmp(str1, str2);

	printf("strcmp(%s, %s) == %d\n", str1, str2, ret);
    return ret;
}

int isInTheVector(sort_indexfav *v, int n, int favorite) {
    int i;

    for(i = 0; i < n; i++) {
        if(v[i].FAVORITE_COUNT == favorite) {
            return 1;
        }
    }
    return 0;
}

int createIndex(FILE *fd) {

    FILE *idxFav;
	FILE *idxLang;
    int i = 0, j = 0, length, k, m = 0, offset;
    char str_aux[141];
	char language[20];
    TWEET t;
    sort_indexfav *vector = NULL;
	sort_indexlang *vectorlang = NULL;
    //vector = NULL;
    //vector = malloc(0);

    idxFav = fopen("idxFav.bin", "wb+");
	idxLang = fopen("idxLang.bin", "wb+");

    rewind(fd);

    fseek(fd, sizeof(int), SEEK_CUR);

    while(1) {
        //offset = ftell(fd);
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
		strcpy(language, str_aux);
        fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
        vector = (sort_indexfav *) realloc(vector, (i+1) * sizeof(sort_indexfav));
		vectorlang = (sort_indexlang *) realloc(vectorlang, (i+1) * sizeof(sort_indexlang));

        vector[m].FAVORITE_COUNT = t.FAVORITE_COUNT;
        vector[m].rrn = i;
		vectorlang[m].rrn = i;
		strcpy(vectorlang[m].language, language);
		//vector[m].offset = offset;
        i++;
        m++;

        //printf("%d %d\n", vector[m].FAVORITE_COUNT, vector[m].rrn);
        //fwrite(&t.FAVORITE_COUNT, sizeof(int), 1, idx);
        //fwrite(&i, sizeof(int), 1, idx);
        fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
        fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
    }

    int vector_length = m;

    printf("vector_length: %d\n", vector_length);

    qsort(vector, i, sizeof(sort_indexfav), compare);
	qsort(vectorlang, i, sizeof(sort_indexlang), comparelang);

    for(k = 0; k < m; k++) {
        fwrite(&vector[k].FAVORITE_COUNT, sizeof(int), 1, idxFav);
        fwrite(&vector[k].rrn, sizeof(int), 1, idxFav);
		fwrite(&vectorlang[k].language, sizeof(char), 20, idxLang);
        fwrite(&vectorlang[k].rrn, sizeof(int), 1, idxLang);
		//fwrite(&vector[k].offset, sizeof(int), 1, idxFav);
        //printf("%d %d\n", vector[k].FAVORITE_COUNT, vector[k].rrn);
    }

    testIndex(idxFav, idxLang);
    fclose(idxFav);
	fclose(idxLang);
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
