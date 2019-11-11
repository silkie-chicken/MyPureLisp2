#include "reader.h"
#include <stdio.h>

int main(void){
	Reader* r = reader_new();
	reader_append(r, token_new("t1"));
	reader_append(r, token_new("t2"));
	for (;reader_cur(r) != NULL;reader_next(r)){
		printf("%s\n", reader_cur(r));
	}
	reader_free(r);

	char input[] = "(nu..n\"unu) ho 'lew 0.332 .234 ho/#$%&!?[}{][g. . ( \"\" (' ;))";
	printf("input: \"%s\"\n", input);
	r =  tokenize(input);
	for (;reader_cur(r) != NULL;reader_next(r)){
		printf("%s ", reader_cur(r));
	}
	printf("\nisNum%c: %d\n", '0', isNum('0'));
	printf("isNum %c: %d\n", '9', isNum('9'));
	printf("isNum %c: %d\n", '0'-1, isNum('0'-1));
	printf("isNum %c: %d\n", '9'+1, isNum('9'+1));
	printf("Alphabet %c: %d\n", 'Z', isAlphabet('Z'));
}

