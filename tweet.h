#ifndef __TWEET_H__
#define __TWEET_H__

typedef struct tweet {
	char* USER;
	char* TEXT;
	char* COORDINATES;
	char* LANGUAGE;

	int FAVORITE_COUNT;
	int RETWEET_COUNT;
	long VIEWS_COUNT;
} TWEET;

typedef struct tweet_list {
	TWEET* node;
	unsigned int offset;

	struct tweet_list* nextNode;
} TweetList;

int addTweet(FILE*, TWEET*);
int removeTweet(FILE*, int);
int readAllTweets(FILE*);

int getTweetByUser(FILE*, char*);
TweetList* getTweetByLanguage(FILE*, char*);
TweetList* getTweetByFavorite(FILE*, int);
TweetList* getMatchingTweet(FILE*, char*, int);

#endif
