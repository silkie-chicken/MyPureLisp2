#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "types.h"
#include "reader.h"
#include "parser.h"

void test(char* input, Env* env){
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
	val_println(eval(ast, env));
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int main(void){
	char buf[200];
	Env* env = env_new();
	for(;;){
		for(int i=0; i<200; i++){
			char c = getchar();
			if (c == '\n') {
				buf[i] = '\0';
				break;
			}
			buf[i] = c;
		}
		test(buf, env);
	}
	return 0;
}
