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

typedef struct sort_indexfav {
    int FAVORITE_COUNT;
    int rrn;
    struct sort_indexfav* next;
} sort_indexfav;

typedef struct sort_indexlang {
    char language[20];
    int rrn;
    struct sort_indexlang* next;
} sort_indexlang;

void write(FILE *fd);
void createIndex(FILE *fp);

/**
 * @brief Insere registros no arquivo a partir
 * da leitura dos dados
 *
 * @param fd Descritor do arquivo
 * @param tweet Registro a ser adicionado
 *
 * @return -1 Se falhou a inserção
 *          1 Se inseriou com sucesso
 */
int addTweet(FILE* fd, TWEET* tweet, int *totalRegs);

/**
 * @brief Remove tweet a partir do campo FAVORITE_COUNT
 *
 * @param fd Descritor do arquivo
 * @param favorite Campo utilizado para buscar
 * o tweet a ser removido
 *
 * @return -1 Se falhou a remoção
 *          1 Se removido com sucesso
 */
int removeTweet(FILE* fd, int favorite);

/**
 * @brief Recupera todos os tweets do arquivo
 * e imprime na tela
 *
 * @param fd Descritor de arquivo
 *
 * @return -1 Se falha na recuperação ou impressão
 *          1 Se recuperado e impresso com sucesso
 */
int readAllTweets(FILE* fd);

/**
 * @brief Recupera todos os tweets referentes ao
 * @p user e imprime na tela
 *
 * @param fd Descritor do arquivo
 * @param user Username utilizado para buscar e
 * imprimir os tweets
 *
 * @return -1 Se falha na recuperação ou impressão
 *          1 Se recuperado e impresso com sucesso
 */
void getTweetByUser(FILE* fd, char* user);

/**
 * @brief Recupera todos os tweets referentes ao
 * @p language
 *
 * @param fd Descritor do arquivo
 * @param language Campo utilizado para buscar os
 * tweets
 *
 * @return Lista com todos os tweets encontrados
           NULL se não encontrou nenhum tweet
 */
TweetList* getTweetByLanguage(FILE* fd, char* language);

/**
 * @brief Recupera todos os tweets referentes ao
 * @p favorite
 *
 * @param fd Descritor do arquivo
 * @param language Campo utilizado para buscar os
 * tweets
 *
 * @return Lista com todos os tweets encontrados
           NULL se não encontrou nenhum tweet
 */
TweetList* getTweetByFavorite(FILE* fd, int favorite);

/**
 * @brief Recupera todos os tweets que estão em
 * ambos os arquivos
 *
 * @param fd Descritor do arquivo
 * @param language Campo utilizado para buscar os
 * tweets
 * @param favorite Campo utilizado para buscar os tweets
 *
 * @return Lista com todos os tweets que deram match
           NULL se não encontrou nenhum tweet
 */
TweetList* getMatchingTweet(FILE* fd, char* language, int favorite);

#endif
