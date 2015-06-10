#include <stdio.h>
#include "tweet.h"

int main(){

    FILE *fd;

    fd = fopen("data.bin", "wb+");

    write(fd);
    readAllTweets(fd);

    return 0;
}