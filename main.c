/**
 * Arnaldo Stanzani					 8937510
 * Guilherme Gonçalves				 8937055
 * Guilherme Silva dos Anjos		 8936830
 * Gustavo Henrique Oliveira Aguiar	 8936912
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tweet.h"

// Remove o \n do final da string
void chomp(char str[]) {
	int pos = 0;

	while (str[pos] && str[pos] != '\n') {
		pos++;
	}
	str[pos] = '\0';

	return;
}

char *allocatesStr(int strLen) {
	char *s;

	s = (char *) malloc (strLen * sizeof(char));

	return s;	
}

int getTweet(void) {
	TWEET t;
	int opt = 1;
	char str[100], *s;
	//int freeByteOffset;

	//fgetc(stdin);
//	while(opt != 0){
		// Le todas as variaveis do registro
		//system("clear");
		//freeByteOffset = searchFreeByteOffset();
		printf("Digite o texto: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.TEXT = s;
		puts(t.TEXT);

		memset(str, 0, 100);
		s = NULL;
		printf("Digite o nome de usuario: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.TEXT = s;
		puts(t.USER);

		memset(str, 0, 100);
		s = NULL;

		printf("Digite as coordenadas: ");
		fgets(t.COORDINATES, COOR_SIZE, stdin);
		chomp(t.COORDINATES);
		fflush(stdin);
		printf("Digite o idioma: ");
		fgets(t.LANGUAGE, LANG_SIZE, stdin);
		chomp(t.LANGUAGE);
		fflush(stdin);
		printf("Digite o numero de marcacoes como favorito: ");
		scanf("%d", &t.FAVORITE_COUNT);
		printf("Digite o numero de retweets: ");
		scanf("%d", &t.RETWEET_COUNT);
		printf("Digite o numero de visualizacoes: ");
		scanf("%ld", &t.VIEWS_COUNT);

		if (addTweet(fp, t) != 0) {
			printf("Insercao nao realizada, tente de novo mais tarde:/\n");
		}
		else {
			printf("Insercao realizada com sucesso!\n");
		}

		printf("Deseja adicionar mais pessoas? \nDigite qualquer numero para sim e 0 para retornar ao menu principal\n");
		scanf("%d", &opt);
		getchar();*/
//	}
	return 0;
}

int main (void) {

	getTweet();

	return 0;
}
