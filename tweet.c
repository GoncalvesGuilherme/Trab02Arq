/**
* Arnaldo Stanzani                  8937510
* Guilherme Gonçalves               8937055
* Guilherme Silva dos Anjos         8936830
* Gustavo Henrique Oliveira Aguiar  8936912
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tweet.h"

char* alloc_str(int size) {
	char* str;
	str = (char *) malloc(size * sizeof(char));

	return str;
}

void printTweet(TWEET t) {
	printf("\t\tTWEET:\n");
	printf("USER: %s\n", t.USER);
	printf("TEXT: %s\n", t.TEXT);
	printf("COORDINATES: %s\n", t.COORDINATES);
	printf("LANGUAGE: %s\n", t.LANGUAGE);
	printf("FAVORITE_COUNT: %d\n", t.FAVORITE_COUNT);
	printf("RETWEET_COUNT: %d\n", t.RETWEET_COUNT);
	printf("VIEWS_COUNT: %ld\n", t.VIEWS_COUNT);
}

int readAllTweets(FILE* fd) {
	int length, i = 0;
	char str_aux[141];
	TWEET t;

	rewind(fd);

	fseek(fd, sizeof(int), SEEK_CUR);

	while(1) {
		fread(&length, sizeof(int), 1, fd); // Ve o tamanho do proximo registro
		if(feof(fd))
			break;
		i = 0;
		while((str_aux[i] = fgetc(fd)) != '|') {
			i++;
		}
		str_aux[i] = '\0';
		printf("%s\n", str_aux);
		if(str_aux[0] != '*') {
			t.USER = alloc_str(strlen(str_aux));
			strcpy(t.USER, str_aux);
			i = 0;
			while((str_aux[i] = fgetc(fd)) != '|') {
				i++;
			}
			str_aux[i] = '\0';
			t.TEXT = alloc_str(strlen(str_aux));
			strcpy(t.TEXT, str_aux);
			i = 0;
			while((str_aux[i] = fgetc(fd)) != '|') {
				i++;
			}
			str_aux[i] = '\0';
			t.COORDINATES = alloc_str(strlen(str_aux));
			strcpy(t.COORDINATES, str_aux);
			i = 0;
			while((str_aux[i] = fgetc(fd)) != '|') {
				i++;
			}
			str_aux[i] = '\0';
			t.LANGUAGE = alloc_str(strlen(str_aux));
			strcpy(t.LANGUAGE, str_aux);
			fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
			fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
			fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
			printTweet(t);
		}
		else {
			fseek(fd, length - (i+1), SEEK_CUR);
		}
	}
	return 0;
}

void getTweetByUser(FILE* fd, char* user) {
	int length, i = 0;
	char str_aux[100];
	TWEET t;

	rewind(fd);
	fseek(fd, sizeof(int), SEEK_CUR);
	while(1) {
		fread(&length, sizeof(int), 1, fd);
		for (; (str_aux[i] = getc(fd)) != '|'; i++) {
			if (feof(fd)) {
				return;
			}
		}

		str_aux[i] = '\0';
		if (strcmp(str_aux, user) == 0) {
			t.USER = alloc_str(strlen(str_aux));
			strcpy(t.USER, str_aux);
			i = 0;
			while((str_aux[i] = fgetc(fd)) != '|') {
				i++;
			}
			str_aux[i] = '\0';
			t.TEXT = alloc_str(strlen(str_aux));
			strcpy(t.TEXT, str_aux);
			i = 0;
			while((str_aux[i] = fgetc(fd)) != '|') {
				i++;
			}
			str_aux[i] = '\0';
			t.COORDINATES = alloc_str(strlen(str_aux));
			strcpy(t.COORDINATES, str_aux);
			i = 0;
			while((str_aux[i] = fgetc(fd)) != '|') {
				i++;
			}
			str_aux[i] = '\0';
			t.LANGUAGE = alloc_str(strlen(str_aux));
			strcpy(t.LANGUAGE, str_aux);
			fread(&t.FAVORITE_COUNT, sizeof(int), 1, fd);
			fread(&t.RETWEET_COUNT, sizeof(int), 1, fd);
			fread(&t.VIEWS_COUNT, sizeof(long), 1, fd);
			printTweet(t);
		}
		else {
			fseek(fd, length - (i+1), SEEK_CUR);
		}
	}
}

int calculatesTweetSize(TWEET *t) {
	int size;

	size = 2 * sizeof(int) + sizeof(long); // size somente dos int e do long, sem as strings

	size += strlen(t->TEXT) * sizeof(char) + strlen(t->USER) * sizeof(char) +
	strlen(t->COORDINATES) * sizeof(char) + strlen(t->LANGUAGE) * sizeof(char);
	return size;
}

/***** FUNCAO TESTE *****/

void testIndex(FILE *fd, FILE *fd2) {
	int favorite, i, j;
	char language[20];

	rewind(fd);
	rewind(fd2);
	while (1) {
		fread(&favorite, sizeof(int), 1, fd);
		fread(&language, sizeof(char), 20, fd2);
		if (feof(fd)) {
			break;
		}

		fread(&i, sizeof(int), 1, fd);
		fread(&j, sizeof(int), 1, fd2);
		printf("%d %d\n", favorite, i);
		printf("%s %d\n", language, j);
	}
}

void testList(FILE* fav, FILE* lang) {
	int favorite;
	char language[20];
	int aux;

	rewind(fav);
	rewind(lang);
	while (1) {
		fread(&favorite, sizeof(int), 1, fav);
		fread(&language, sizeof(char), 20, lang);
		if (feof(fav) && feof(lang)) {
			break;
		}

		if (!feof(lang)) {
			printf("%s ", language);
			while ((aux = fgetc(lang)) != '#' && !feof(lang)) {
				if (aux == '|') {
					continue;
				}

				printf("%d ", aux);
			}
		}

		if (!feof(fav)) {
			printf("%d ", favorite);
			while ((aux = fgetc(lang)) != '#' && !feof(fav)) {
				if (aux == '|') {
					continue;
				}

				printf("%d ", aux);
			}
		}
	}
}

/**********************************/

int compare(const void *a, const void *b) {
	return ((*(sort_indexfav*)a).FAVORITE_COUNT - (*(sort_indexfav*)b).FAVORITE_COUNT);
}

int comparelang(const void *a, const void *b) {
	char* str1 = (*(sort_indexlang *)a).language;
	char* str2 = (*(sort_indexlang *)b).language;

	return strcmp(str1, str2);
}

int isInFavSet(sort_indexfav* set, int element) {
	for (; set != NULL; set = set->next) {
		if (set->FAVORITE_COUNT == element) {
			return 1;
		}
	}

	return 0;
}

int isInLangSet(sort_indexlang* set, char* element) {
	for (; set != NULL; set = set->next) {
		if (strcmp(set->language, element) == 0) {
			return 1;
		}
	}

	return 0;
}

typedef struct simple_map_list_int {
	struct simple_map_list_int* next;
	int FAVORITE_COUNT;
	sort_indexfav* begin;
	sort_indexfav* end;
} map_list_fav;

typedef struct simple_map_list_char {
	struct simple_map_list_char* next;
	char language[20];
	sort_indexlang* begin;
	sort_indexlang* end;
} map_list_lang;

void createInvertedList(FILE* fd, FILE* idxFav, FILE* idxLang) {
	if (!fd || !idxLang || !idxFav) {
		return;
	}

	FILE* listFileFav = fopen("listFav.bin", "wb+");
	FILE* listFileLang = fopen("listLang.bin", "wb+");

	if (!listFileFav || !listFileLang) {
		return;
	}

	map_list_fav* listFav = NULL;
	map_list_lang* listLang = NULL;

	map_list_fav* firstListFav = NULL;
	map_list_lang* firstListLang = NULL;

	int favcount = 0, rrn = 0;;
	char language[20];

	rewind(fd);
	rewind(idxFav);
	rewind(idxLang);
	while (1) {
		fread(&favcount, sizeof(int), 1, idxFav);
		fread(&rrn, sizeof(int), 1, idxFav);
		if (!feof(idxFav)) {
			listFav = (map_list_fav*) malloc(sizeof(map_list_fav));
			listFav->FAVORITE_COUNT = favcount;
			listFav->end = (sort_indexfav*) malloc(sizeof(sort_indexfav));
			listFav->end->FAVORITE_COUNT = favcount;
			listFav->end->rrn = rrn;

			if (!listFav->begin) {
				listFav->begin = listFav->end;
			}

			if (!firstListFav) {
				firstListFav  = listFav;
			}

			listFav->end = listFav->end->next;
			listFav = listFav->next;
		}

		fread(&language, sizeof(char), 20, idxLang);
		fread(&rrn, sizeof(int), 1, idxLang);
		if (!feof(idxLang)) {
			listLang = (map_list_lang*) malloc(sizeof(map_list_lang));
			strcpy(listLang->language, language);
			listLang->end = (sort_indexlang*) malloc(sizeof(sort_indexlang));
			strcpy(listLang->end->language, language);
			listLang->end->rrn = rrn;

			if (!listLang->begin) {
				listLang->begin = listLang->end;
			}

			if (!firstListLang) {
				firstListLang  = listLang;
			}

			listLang->end = listLang->end->next;
			listLang = listLang->next;
		}

		if (feof(idxLang) && feof(idxFav)) {
			break;
		}
	}

	int i = 0;
	while (1) {
		int end_of_file = 0;
		for (int k = 0; k < 3; k++) {
			while (fgetc(fd) != '|') {
				if (feof(fd)) {
					end_of_file = 1;
					break;
				}
			}
		}

		if (end_of_file) {
			break;
		}

		int length = 0;
		char str_aux[141];
		for (; (str_aux[length] = fgetc(fd)) != '|'; length++);

		str_aux[length] = '\0';
		fread(&favcount, sizeof(int), 1, fd);

		for (map_list_lang* node = firstListLang; node != NULL; node = node->next) {
			if (strcmp(str_aux, node->language) == 0) {
				node->end = (sort_indexlang*) malloc(sizeof(sort_indexlang));
				strcpy(node->end->language, language);
				node->end->rrn = i;

				node->end = node->end->next;
			}
		}

		for (map_list_fav* node = firstListFav; node != NULL; node = node->next) {
			if (node->FAVORITE_COUNT == favcount) {
				node->end = (sort_indexfav*) malloc(sizeof(sort_indexfav));
				node->end->FAVORITE_COUNT = favcount;
				node->end->rrn = i;

				node->end = node->end->next;
			}
		}

		i++;
	}

	char registerdelimiter = '#';
	char delimiter = '|';
	for (map_list_fav* node = firstListFav; node != NULL; node = node->next) {
		fwrite(&node->FAVORITE_COUNT, sizeof(int), 1, listFileFav);
		for (sort_indexfav* index_node = node->begin; index_node != NULL; index_node = index_node->next) {
			fwrite(&index_node->rrn, sizeof(int), 1, listFileFav);
			fwrite(&delimiter, sizeof(char), 1, listFileFav);
		}
		fwrite(&registerdelimiter, sizeof(char), 1, listFileFav);
	}

	for (map_list_lang* node = firstListLang; node != NULL; node = node->next) {
		fwrite(&node->language, sizeof(char), 20, listFileLang);
		for (sort_indexlang* index_node = node->begin; index_node != NULL; index_node = index_node->next) {
			fwrite(&index_node->rrn, sizeof(int), 1, listFileLang);
			fwrite(&delimiter, sizeof(char), 1, listFileLang);
		}
		fwrite(&registerdelimiter, sizeof(char), 1, listFileLang);
	}

	fclose(listFileLang);
	fclose(listFileFav);
}

void createIndex(FILE *fd) {
	if (!fd) {
		return;
	}

	int i = 0;
	int favcount = 0, fav_set_size = 0, lang_set_size = 0;

	sort_indexlang* lang_set = NULL;
	sort_indexlang* first_nodelang = NULL;

	sort_indexfav* fav_set = NULL;
	sort_indexfav* first_nodefav = NULL;

	rewind(fd);
	fseek(fd, sizeof(int), SEEK_CUR);
	while (1) {
		int end_of_file = 0;
		for (int k = 0; k < 3; k++) {
			while (fgetc(fd) != '|') {
				if (feof(fd)) {
					end_of_file = 1;
					break;
				}
			}
		}

		if (end_of_file) {
			break;
		}

		int length = 0;
		char str_aux[141];
		for (; (str_aux[length] = fgetc(fd)) != '|'; length++);

		str_aux[length] = '\0';
		fread(&favcount, sizeof(int), 1, fd);

		if (!isInFavSet(fav_set, favcount)) {
			sort_indexfav* prev = NULL;
			for (fav_set = first_nodefav; fav_set; fav_set = fav_set->next) {
				prev = fav_set;
			}

			if (!fav_set) {
				fav_set = (sort_indexfav*) malloc(sizeof(sort_indexfav));
				if (prev) {
					prev->next = fav_set;
				}
			}

			if (!first_nodefav) {
				first_nodefav = fav_set;
			}

			fav_set->FAVORITE_COUNT = favcount;
			fav_set->rrn = i;
			fav_set_size++;
		}

		if (!isInLangSet(lang_set, str_aux)) {
			sort_indexlang* prev = NULL;
			for (lang_set = first_nodelang; lang_set; lang_set = lang_set->next) {
				prev = lang_set;
			}

			if (!lang_set) {
				lang_set = (sort_indexlang*) malloc(sizeof(sort_indexlang));
				if (prev) {
					prev->next = lang_set;
				}
			}

			if (!first_nodelang) {
				first_nodelang = lang_set;
			}

			strcpy(lang_set->language, str_aux);
			lang_set->rrn = i;
			lang_set_size++;
		}

		i++;
	}

	sort_indexfav fav_vector[fav_set_size];
	sort_indexlang lang_vector[lang_set_size];

	i = 0;
	for (sort_indexlang* node = first_nodelang; node != NULL; node = node->next, i++) {
		strcpy(lang_vector[i].language, node->language);
		lang_vector[i].rrn = node->rrn;
	}


	i = 0;
	for (sort_indexfav* node = first_nodefav; node != NULL; node = node->next, i++) {
		fav_vector[i].FAVORITE_COUNT = node->FAVORITE_COUNT;
		fav_vector[i].rrn = node->rrn;
	}

	qsort(fav_vector, fav_set_size, sizeof(sort_indexfav), compare);
	qsort(lang_vector, lang_set_size, sizeof(sort_indexlang), comparelang);

	FILE* idxFav = fopen("idxFav.bin", "wb+");
	FILE* idxLang = fopen("idxLang.bin", "wb+");

	if (!idxFav || !idxLang) {
		return;
	}

	for (int k = 0; k < lang_set_size; k++) {
		fwrite(&fav_vector[k].FAVORITE_COUNT, sizeof(int), 1, idxFav);
		fwrite(&fav_vector[k].rrn, sizeof(int), 1, idxFav);
	}

	for (int k = 0; k < fav_set_size; k++) {
		fwrite(&lang_vector[k].language, sizeof(char), 20, idxLang);
		fwrite(&lang_vector[k].rrn, sizeof(int), 1, idxLang);
	}

	createInvertedList(fd, idxFav, idxLang);

	fclose(idxFav);
	fclose(idxLang);
}

int addEnd(FILE *fp, TWEET *t, int totalSize, int *totalRegs) {
	char delimiter = '|';
	char text[strlen(t->TEXT)];
	char user[strlen(t->USER)];
	char coordinates[strlen(t->COORDINATES)];
	char language[strlen(t->LANGUAGE)];
	int favorite, retweet;
	long views;

	strcpy(text, t->TEXT);
	strcpy(user, t->USER);
	strcpy(coordinates, t->COORDINATES);
	strcpy(language, t->LANGUAGE);
	favorite = t->FAVORITE_COUNT;
	retweet = t->RETWEET_COUNT;
	views = t->VIEWS_COUNT;

	fseek(fp, 0, SEEK_END);

	fwrite(&totalSize, sizeof(int), 1, fp);
	fwrite(user, strlen(user), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(text, strlen(text), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(coordinates, strlen(coordinates), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(language, strlen(language), 1, fp);
	fwrite(&delimiter, sizeof(char), 1, fp);
	fwrite(&favorite, sizeof(int), 1,fp);
	fwrite(&retweet, sizeof(int), 1, fp);
	fwrite(&views, sizeof(long), 1, fp);

	*totalRegs += 1;
	if (*totalRegs == 10) {
		createIndex(fp);
	}

	return 0;
}

int addMiddle(FILE *fp, TWEET *t, int totalSize, int *totalRegs) {
	return 0;
}

int addTweet(FILE *fp, TWEET *newTweet, int *totalRegs) {
	int stackTop, totalSize;

	totalSize = calculatesTweetSize(newTweet);
	rewind(fp);
	fread(&stackTop, sizeof(int), 1, fp);

	if (stackTop == -1) {
		return addEnd(fp, newTweet, totalSize, totalRegs);
	}
	else {
		return addMiddle(fp, newTweet, totalSize, totalRegs);
	}

	return 0;
}
