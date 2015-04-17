#include <stdio.h>
#include <stdlib.h>

#include "crossword.h"

void importBoard(FILE *file) {
	int info[100][100];
	int *loc[2], count[2], wnum = 0;
	int i, j;
	
	fscanf(file, "%d %d", &board.y, &board.x);
	
	for(i = 0; i < board.y; i++)
		for(j = 0; j < board.x; j++)
			fscanf(file, "%d", &info[i][j]);
	
	for(i = 0; i < board.y; i++) {
		fscanf(file, "%s", board.space[i]);
		
		for(j = 0; j <= board.x; j++) {
			if(board.space[i][j] == '?') board.space[i][j] = '.';
			else if(board.space[i][j] == '*') board.space[i][j] = '\0';
			
			board.spaceT[j][i] = board.space[i][j];
		}
	}
	
	for(j = 0; j <= board.x; j++)
		board.spaceT[j][i] = board.space[i][j] = '\0';
	
	board.num = 0;
	for(i = 0; i < 2; i++) {
		int num;
		
		fscanf(file, "%d", &num);
		loc[i] = (int *) malloc(sizeof(int) * (num+1));
		
		board.num += num;
		
		for(j = 0; j < num; j++) fscanf(file, "%d", &loc[i][j]);
		loc[i][num] = 0;
	}
	board.word = (struct __word *) malloc(sizeof(struct __word) * board.num);
	count[0] = count[1] = 0;
	
	for(i = 0; i < board.y; i++) {
		for(j = 0; j < board.x; j++) {
			if(info[i][j] <= 0) continue;
			
			if(loc[ACROSS][count[ACROSS]] != 0) {
				if(loc[ACROSS][count[ACROSS]] == info[i][j]) {
					board.word[wnum].way = ACROSS;
					board.word[wnum].y = i;
					board.word[wnum].x = j;
					board.word[wnum++].head = &board.space[i][j];
					
					++count[ACROSS];
				}
			}
			if(loc[DOWN][count[DOWN]] != 0) {
				if(loc[DOWN][count[DOWN]] == info[i][j]) {
					board.word[wnum].way = DOWN;
					board.word[wnum].y = i;
					board.word[wnum].x = j;
					board.word[wnum++].head = &board.spaceT[j][i];
					
					++count[DOWN];
				}
			}
		}
	}
}

void syncBoard(struct __word *word) {
	int i;
	
	if(word->way == ACROSS)
		for(i = word->x; word->head[i-word->x] != '\0'; i++)
			board.spaceT[i][word->y] = board.space[word->y][i];
	else
		for(i = word->y; word->head[i-word->y] != '\0'; i++)
			board.space[i][word->x] = board.spaceT[word->x][i];
}

void printBoard() {
	int i, j;
	
	for(i = 0; i < board.y; i++) {
		for(j = 0; j < board.x; j++)
			if(board.space[i][j] == '\0') board.space[i][j] = '*';
		
		printf("%s\n", board.space[i]);
	}
}