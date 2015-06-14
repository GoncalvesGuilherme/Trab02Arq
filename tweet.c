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

    int length, i = 0, j;
    char str_aux[141];
    TWEET t;

    rewind(fd);

    while(1) {
        //fread(&j, sizeof(int), 1, fd);
        fseek(fd, sizeof(int), SEEK_CUR);
        fread(&length, sizeof(int), 1, fd); // Ve o tamanho do proximo registro
        if(feof(fd))
            break;
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '#') {
            i++;
        }
        str_aux[i] = '\0';
        if(str_aux[0] != '*') {
            t.USER = alloc_str(strlen(str_aux));
            strcpy(t.USER, str_aux);
            //printf("%s\n", t.USER);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '#') {
                i++;
            }
            str_aux[i] = '\0';
            t.TEXT = alloc_str(strlen(str_aux));
            strcpy(t.TEXT, str_aux);
            //printf("%s\n", t.TEXT);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '#') {
                i++;
            }
            str_aux[i] = '\0';
            t.COORDINATES = alloc_str(strlen(str_aux));
            strcpy(t.COORDINATES, str_aux);
            //printf("%s\n", t.COORDINATES);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '#') {
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
            fseek(fd, length - (strlen(str_aux) + sizeof(int)) - 1, SEEK_CUR);
        }
    }
    return 0;
}

int getTweetByUser(FILE* fd, char* user) {

    int length, i = 0, j;
    char str_aux[100];
    TWEET t;

    rewind(fd);

    while(1) {
        //fread(&j, sizeof(int), 1, fd);
        fseek(fd, sizeof(int), SEEK_CUR);
        fread(&length, sizeof(int), 1, fd);
        if(feof(fd))
            break;
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '#') {
            i++;
        }
        //printf("ftell antes do if: %d\n", (int)ftell(fd));
        //printf("%s\n", str_aux);
        //printf("%d %ld\n", (int)strlen(str_aux), ftell(fd));
        str_aux[i] = '\0';
        if(strcmp(str_aux, user) == 0) {
            t.USER = alloc_str(strlen(str_aux));
            strcpy(t.USER, str_aux);
            //printf("%s\n", t.USER);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '#') {
                i++;
            }
            str_aux[i] = '\0';
            t.TEXT = alloc_str(strlen(str_aux));
            strcpy(t.TEXT, str_aux);
            //printf("%s\n", t.TEXT);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '#') {
                i++;
            }
            str_aux[i] = '\0';
            t.COORDINATES = alloc_str(strlen(str_aux));
            strcpy(t.COORDINATES, str_aux);
            //printf("%s\n", t.COORDINATES);
            i = 0;
            while((str_aux[i] = fgetc(fd)) != '#') {
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
            fseek(fd, length - (strlen(str_aux) + sizeof(int)) - 1, SEEK_CUR);
        }
        //printf("ftell depois do if: %d\n", (int)ftell(fd));
    }
    return 0;
}

void write(FILE *fd) {
    int x = 61;
    int j = 4;
    char str[] = "Arnaldo#";
    char str2[] = "Isso eh um teste#";
    char str3[] = "3N24L#";
    char str4[] = "Portugues#";
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

    strcpy(str, "*ose#");
    strcpy(str2, "Teste profundo#");
    strcpy(str3, "24N24W#");
    strcpy(str4, "Ingles#");
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

    strcpy(str, "Giovanna#");
    strcpy(str2, "Testeeeeeeee#");
    strcpy(str3, "11N11W#");
    strcpy(str4, "Frances#");
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

int addTweet(FILE *fp, TWEET *newTweet) {


}