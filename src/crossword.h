#define ACROSS	0
#define DOWN	1

struct __word {
	char *head;
	int x, y, way;
};

struct __board {
	char space[101][101];
	char spaceT[101][101];
	int x, y;
	
	struct __word *word;
	int num;
} board;

void importBoard(FILE *file);
void syncBoard(struct __word *word);
void printBoard();