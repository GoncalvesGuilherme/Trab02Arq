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
void chomp(char str[]);

char *allocatesStr(int strLen);

int getTweet(FILE *fp);

int main (void) {
	int sp = -1, sp1;
	FILE *fp;

	fp = fopen("data.bin", "ab+");
	fwrite(&sp, sizeof(int), 1, fp);

	//fseek(fp, 0, SEEK_SET);
	//fread(&sp1, sizeof(int), 1, fp);
	//printf("sp1 %d\n", sp1);

	getTweet(fp);

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

int getTweet(FILE *fp) {
	TWEET t;
	int opt = 1;
	char str[100], *s;
	int freeByteOffset;

	//fgetc(stdin);
	//fgets(str, 100, stdin);		// ignora a primeira chamada por pegar lixo, estranho nao deu problema no inicio, tirei essa e works

	while(opt != 0){
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
		t.USER = s;
		puts(t.USER);

		memset(str, 0, 100);
		s = NULL;
		printf("Digite as coordenadas: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.COORDINATES = s;
		puts(t.COORDINATES);

		printf("Digite o idioma: ");
		fgets(str, 100, stdin);
		chomp(str);
		s = allocatesStr(strlen(str));
		strcpy(s, str);
		t.LANGUAGE = s;
		puts(t.LANGUAGE);

		printf("Digite o numero de marcacoes como favorito: ");
		scanf("%d", &t.FAVORITE_COUNT);
		printf("fc %d\n", t.FAVORITE_COUNT);

		printf("Digite o numero de retweets: ");
		scanf("%d", &t.RETWEET_COUNT);
		printf("rc %d\n", t.RETWEET_COUNT);

		printf("Digite o numero de visualizacoes: ");
		scanf("%ld", &t.VIEWS_COUNT);
		printf("vc %ld\n", t.VIEWS_COUNT);

		if (addTweet(fp, &t) != 0) {
			printf("Insercao nao realizada, tente de novo mais tarde:/\n");
		}
		else {
			printf("Insercao realizada com sucesso!\n");
		}

		printf("Deseja adicionar mais pessoas? \nDigite qualquer numero para sim e 0 para retornar ao menu principal\n");
		scanf("%d", &opt);
		//getchar();

		fgets(str, 100, stdin);		// ignora o lixo da strin
	}
	return 0;
}
