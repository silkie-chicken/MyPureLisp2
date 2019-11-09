#include <stdio.h>
#include "types.h"

int main(void){
	Val* i = new_integer(3);
	Val* s = new_symbol("symbol");
	Val* p = new_pair(i, s);
	printf("pair (%ld %s)\n", p->val.pair->l->val.integer, p->val.pair->r->val.string);
}


