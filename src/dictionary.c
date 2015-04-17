#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#include "dictionary.h"

void exportNewDict();
int compare(const void *a, const void *b);

void importDict() {
	FILE *file;
	int temp = -1;
	int i, j;
	
	file = fopen("dict_new.txt", "r");
	if(!file) {
		exportNewDict();
		
		file = fopen("dict_new.txt", "r");
		if(!file) exit(1);
	}
	else for(i = 0; i < NUMWORDS; i++) fscanf(file, "%s", dict.word[i]);
	
	for(i = 0; i < MAXLEN; i++) dict.index[i] = 0;
	for(i = 0; i < NUMWORDS; i++) {
		if(temp < (int) strlen(dict.word[i]) - 1) dict.index[++temp] = i;
		
		for(j = 0; j < (int) strlen(dict.word[i]); j++)
			dict.word[i][j] = (char) toupper(dict.word[i][j]);
	}
	
	fclose(file);
}

int findWords(char *cond, int *idx) {
	regex_t reg;
	regmatch_t mat;
	int range = (int) strlen(cond);
	int count = 0;
	
	int i;
	
	if(regcomp(&reg, cond, REG_EXTENDED|REG_NEWLINE)) {
		regfree(&reg);
		return -1;
	}
	
	for(i = dict.index[range-1]; i < dict.index[range]; i++) {
		if(!regexec(&reg, dict.word[i], 1, &mat, 0))
			idx[count++] = i;
	}
	
	regfree(&reg);
	return count;
}

void exportNewDict() {
	FILE *file;
	int i;
	
	file = fopen("dict.txt", "r");
	
	for(i = 0; i < NUMWORDS; i++) fscanf(file, "%s", dict.word[i]);
	qsort(dict.word, NUMWORDS, sizeof(dict.word[0]), compare);
	fclose(file);
	
	file = fopen("dict_new.txt", "w");
	
	for(i = 0; i < NUMWORDS; i++) fprintf(file, "%s\n", dict.word[i]);
	fclose(file);
}

int compare(const void *a, const void *b) {
	return (int) (strlen((char *) a) - strlen((char *) b));
}