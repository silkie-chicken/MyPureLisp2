#include <stdio.h>
#include "reader.h"
#include "parser.h"

int main(void){
	char input[] = "(+ 3 2 1 0)";
	printf("input: \"%s\"\n", input);
	Reader* r =  tokenize(input);
	for (;reader_cur(r) != NULL;reader_next(r)){
		printf("%s ", reader_cur(r));
	}
	puts(" ");
	Val* ast = parse(r);
	printf("%ld\n", ast->val.integer);
}

