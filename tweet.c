#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tweet.h"

char* alloc_str(int size) {

    char* str;

    str = (char *) malloc(size * sizeof(char));

    return str;
}

int readAllTweets(FILE* fd) {

    int length, i = 0;
    char str_aux[100];
    TWEET t;

    rewind(fd);

    while(1) {
        fread(&length, sizeof(int), 1, fd); // Ve o tamanho do proximo registro
        if(feof(fd))
            break;
        while((str_aux[i] = fgetc(fd)) != '#') {
            i++;
        }
        str_aux[i] = '\0';
        t.USER = alloc_str(strlen(str_aux));
        strcpy(t.USER, str_aux);
        printf("%s\n", t.USER);
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '#') {
            i++;
        }
        str_aux[i] = '\0';
        t.TEXT = alloc_str(strlen(str_aux));
        strcpy(t.TEXT, str_aux);
        printf("%s\n", t.TEXT);
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '#') {
            i++;
        }
        str_aux[i] = '\0';
        t.COORDINATES = alloc_str(strlen(str_aux));
        strcpy(t.COORDINATES, str_aux);
        printf("%s\n", t.COORDINATES);
        i = 0;
        while((str_aux[i] = fgetc(fd)) != '#') {
            i++;
        }
        str_aux[i] = '\0';
        t.LANGUAGE = alloc_str(strlen(str_aux));
        strcpy(t.LANGUAGE, str_aux);
        printf("%s\n", t.LANGUAGE);
        fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
        printf("%d\n", t.FAVORITE_COUNT);
        fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
        printf("%d\n", t.RETWEET_COUNT);
        fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
        printf("%ld\n", t.VIEWS_COUNT);
    }
    return 0;
}

void write(FILE *fd) {
    int x = 10;
    char str[] = "Arnaldo#";
    char str2[] = "Isso eh um teste#";
    char str3[] = "3N24L#";
    char str4[] = "Portugues#";
    int y = 4;
    int z = 8;
    long a = 100;

    rewind(fd);

    fwrite(&x, sizeof(int), 1, fd);
    fwrite(str, sizeof(char), strlen(str), fd);
    fwrite(str2, sizeof(char), strlen(str2), fd);
    fwrite(str3, sizeof(char), strlen(str3), fd);
    fwrite(str4, sizeof(char), strlen(str4), fd);
    fwrite(&y, sizeof(int), 1, fd);
    fwrite(&z, sizeof(int), 1, fd);
    fwrite(&a, sizeof(long), 1, fd);

    strcpy(str, "Jose#");
    strcpy(str2, "Teste profundo#");
    strcpy(str3, "24N24W#");
    strcpy(str4, "Ingles#");
    x = 20;
    y = 14;
    z = 18;
    a = 200;

    fwrite(&x, sizeof(int), 1, fd);
    fwrite(str, sizeof(char), strlen(str), fd);
    fwrite(str2, sizeof(char), strlen(str2), fd);
    fwrite(str3, sizeof(char), strlen(str3), fd);
    fwrite(str4, sizeof(char), strlen(str4), fd);
    fwrite(&y, sizeof(int), 1, fd);
    fwrite(&z, sizeof(int), 1, fd);
    fwrite(&a, sizeof(long), 1, fd);
}