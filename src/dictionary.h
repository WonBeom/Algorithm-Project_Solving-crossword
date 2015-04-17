#define NUMWORDS	99175
#define MAXLEN		23

struct __dict {
	char word[NUMWORDS][MAXLEN+1];
	int index[MAXLEN];
} dict;

void importDict();
int findWords(char *cond, int *idx);