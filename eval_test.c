#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "types.h"
#include "reader.h"
#include "parser.h"

void test(char* input){
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("input: \"%s\"\n", input);
	Reader* r =  tokenize(input);
	printf("tokens: ");
	for (;reader_cur(r) != NULL;reader_next(r)) printf("%s ", reader_cur(r));
	puts(" ");
	reader_peek(r);
	Val* ast = parse(r);
	printf("ast: ");
	val_println(ast);
	printf("eval: ");
	Env* env = env_new();
	val_println(eval(ast, env));
}

int main(void){
	test("()");
	test("(car '(1 2 3))");
	test("'(1 2 3)");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	return 0;
}
