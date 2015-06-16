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
	int opt = 1, fav, totalRegs;
	FILE *fp;
	char str[20];
	fp = fopen("data.bin", "ab+");
	noFile(fp);
	while(opt != 0)
	{
		printf("0 - Sair\n1 - Add\n2 - Imprimir tudo\n3 - Busca por user\n4 - Busca por favorite count\n5 - Busca por language\n6 - Busca por favorite count e language\n7 - Remover\n");
		scanf("%d", &opt);
		switch(opt)
		{
			case 0:
				fclose(fp);
				return 0;
				break;
			case 1:
				getTweet(fp, &totalRegs);
				break;
			case 2:
				readAllTweets(fp);
				break;
			case 3:
				printf("Qual usuario deseja buscar?\n");
				scanf("%s", str);
				getTweetByUser(fp, str);
				break;
			case 4:
				printf("Qual favorite count deseja buscar?\n");
				scanf("%d", &fav);
				break;
			case 5:
				printf("Falha na implementacao :(\n");
				break;
			case 6:
				printf("Falha na implementacao :(\n");
				break;
			case 7:
				printf("Qual favorite count deseja remover?\n");
				scanf("%d", &fav);
				break;
		}
	}
	fclose(fp);

	return 0;
}

void printList(FILE* fd, TweetList *l)
{
	TWEET t;
	char str_aux[141];
	int j;
	while(l != NULL)
	{
		fseek(fd, l->offset + sizeof(int), SEEK_SET);
		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.USER = alloc_str(strlen(str_aux));
        strcpy(t.USER, str_aux);

		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.TEXT = alloc_str(strlen(str_aux));
        strcpy(t.TEXT, str_aux);

		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.COORDINATES = alloc_str(strlen(str_aux));
        strcpy(t.COORDINATES, str_aux);

		for (j = 0; str_aux[j] != '|'; j++, str_aux[j] = getc(fd));
		str_aux[j] = '\0';
		t.LANGUAGE = alloc_str(strlen(str_aux));
        strcpy(t.LANGUAGE, str_aux);

		fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
        fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
        fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
		printTweet(t);
		l = l->nextNode;
	}
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

	fgetc(stdin);
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