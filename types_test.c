#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int main(void){
	Val* i = new_integer(3);
	char* buf = (char*)malloc(sizeof(char)*10);
	sprintf(buf,"hoge");
	Val* s = new_symbol(buf);
	Val* p = new_pair(i, s);
	printf("pair (%ld %s)\n", p->val.pair->l->val.integer, p->val.pair->r->val.string);
	//free_val(p);
	printf("pair (%ld %s)\n", p->val.pair->l->val.integer, p->val.pair->r->val.string);
}


