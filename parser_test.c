#include <stdio.h>
#include "reader.h"
#include "parser.h"

void test(char* input){
	printf("input: \"%s\" ==============\n", input);
	Reader* r =  tokenize(input);
	printf("tokens: ");
	for (;reader_cur(r) != NULL;reader_next(r)){
		printf("%s ", reader_cur(r));
	}
	puts(" ");
	reader_peek(r);
	Val* ast = parse(r);
	printf("ast: ");
	val_println(ast);
}

int main(void){
/*
	test("((a) 32 t nil)");
	test("nil");
	test("()");
	test("'hoge");
	test("'(1 2 3 (hoge '3 nil))");
*/
}


