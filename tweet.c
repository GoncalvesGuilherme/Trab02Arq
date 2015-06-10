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

    int length;
    char str_aux[100];
    TWEET t;

    rewind(fd);

    do {
        fread(length, sizeof(int), 1, fd); // Ve o tamanho do proximo campo
        t.USER = alloc_str(length); // alloca espaco no ponteiro USER
        fread(t.USER, sizeof(char), length, fd); // Salva o USER lido em t.USER
        fseek(fd, sizeof(char), SEEK_CUR); // Pula o delimitador
    } while(!feof(fd));
}