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

void noFile(FILE *fp) {
	int sp = -1, pos;

	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	//printf("pos %d\n", pos);
	if (pos <= 0) {
		rewind(fp);
		fwrite(&sp, sizeof(int), 1, fp);
	}
}

// Remove o \n do final da string
void chomp(char str[]);

char *allocatesStr(int strLen);

int getTweet(FILE *fp, int *totalRegs);

int main (void) {
	int totalRegs = 0;
	FILE* fp = fopen("data.bin", "ab+");
	noFile(fp);

	getTweet(fp, &totalRegs);
	//getTweetByUser(fp, "neymarjr");
	createIndex(fp);
	fclose(fp);

	return 0;
}

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

int getTweet(FILE *fp, int *totalRegs) {
	TWEET t;
	int opt = 1;
	char str[100], *s;

	while(opt != 0){
		// Le todas as variaveis do registro
		printf("Digite o texto: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.TEXT = s;

		memset(str, 0, 100);
		s = NULL;
		printf("Digite o nome de usuario: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.USER = s;

		memset(str, 0, 100);
		s = NULL;
		printf("Digite as coordenadas: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.COORDINATES = s;

		printf("Digite o idioma: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.LANGUAGE = s;

		printf("Digite o numero de marcacoes como favorito: ");
		scanf("%d", &t.FAVORITE_COUNT);

		printf("Digite o numero de retweets: ");
		scanf("%d", &t.RETWEET_COUNT);

		printf("Digite o numero de visualizacoes: ");
		scanf("%ld", &t.VIEWS_COUNT);

		if (addTweet(fp, &t, totalRegs) != 0) {
			printf("Insercao nao realizada, tente de novo mais tarde:/\n");
		} else {
			printf("Insercao realizada com sucesso!\n");
		}

		printf("Deseja adicionar mais pessoas? \nDigite qualquer numero para sim e 0 para retornar ao menu principal\n");
		scanf("%d", &opt);
		getchar();
	}

	return 0;
}