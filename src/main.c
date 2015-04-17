//
//	20123353 Kim Hoyeonjiki
//	Crossword Puzzle
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>

#include "crossword.h"
#include "dictionary.h"

FILE *file;

int fillBoard(int **index, int *num, int curr);
int insertWord(char *from, char *to);

int main(int argc, const char * argv[]) {
	int proc_num, p;
	
	file = fopen("input.txt", "r");
	if(!file) {
		printf("No such file or directory\n");
		exit(1);
	}
	
	fscanf(file, "%d", &proc_num);
	
	importDict();
	
	for(p = 0; p < proc_num; p++) {
		int **index, *num;
		int i;
		
		//clock_t start, fin;
		
		//start = clock();
		
		importBoard(file);
		
		index = (int **) malloc(sizeof(int *) * board.num);
		num = (int *) malloc(sizeof(int *) * board.num);
		
		for(i = 0; i < board.num; i++) {
			index[i] = (int *) malloc(sizeof(int) * 1000);
			num[i] = findWords(board.word[i].head, index[i]);
		}
		
		if (!fillBoard(index, num, 0)) printBoard();
		else printf("Unable to fill in.\n");
		
		for(i = 0; i < board.num; i++) free(index[i]);
		free(index);
		free(num);
		free(board.word);
		
		//fin = clock();
		//printf("%lf\n", (double) (fin - start) / CLOCKS_PER_SEC);
	}
	
	fclose(file);
    return 0;
}

int fillBoard(int **index, int *num, int curr) {
	char copy[100];
	int i;
	
	if(curr == board.num) return 0;
	
	strcpy(copy, board.word[curr].head);
	
	for(i = 0; i < num[curr]; i++) {
		if(!insertWord(dict.word[index[curr][i]], board.word[curr].head)) {
			syncBoard(&board.word[curr]);
			if(!fillBoard(index, num, curr+1)) return 0;
		}
		
		strcpy(board.word[curr].head, copy);
		syncBoard(&board.word[curr]);
	}
	
	return 1;
}

int insertWord(char *from, char *to) {
	int i;
	
	for(i = 0; from[i] != '\0'; i++) {
		if(to[i] != '.' && to[i] != from[i]) return -1;
		to[i] = from[i];
	}
	
	return 0;
}