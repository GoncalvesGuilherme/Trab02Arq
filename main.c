/**
 * Arnaldo Stanzani					 8937510
 * Guilherme Gonçalves				 8937055
 * Guilherme Silva dos Anjos		 8936830
 * Gustavo Henrique Oliveira Aguiar	 8936912
*/

#include <stdio.h>
#include <stdlib.h>
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

int getTweet(void) {
	TWEET t;
	int opt = 1;
	int freeByteOffset;

	fgetc(stdin);
	while(opt != 0){
		// Le todas as variaveis do registro
		system("clear");
		freeByteOffset = searchFreeByteOffset();
		printf("Digite o texto: ");
		fgets(t.TEXT, 100, stdin);
		chomp(t.TEXT);
		fflush(stdin);
		printf("Digite o nome de usuario: ");
		fgets(t.USER, USER_SIZE, stdin);
		chomp(t.USER);
		fflush(stdin);
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
		// Se tiver espaço livre, insere nele
		if(RRNlivre != -1)
			adicionarmeio(t, RRNlivre);
		// Senao, insere no final do arquivo
		else
			adicionarfim(t);
		printf("Deseja adicionar mais pessoas? \nDigite qualquer numero para sim e 0 para retornar ao menu principal\n");
		scanf("%d", &opc);
		getchar();
	}
	return 0;
}
