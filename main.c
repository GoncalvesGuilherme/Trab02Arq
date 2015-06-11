#include <stdio.h>
#include "tweet.h"

int main(){

    FILE *fd;

    fd = fopen("data", "wb+");

    write(fd);
    readAllTweets(fd);
    getTweetByUser(fd, "Arnaldo");
    getTweetByUser(fd, "Jose");
    getTweetByUser(fd, "Giovanna");

    return 0;
}