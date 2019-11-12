#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int main(void){
	char* buf = (char*)malloc(sizeof(char)*5);
	sprintf(buf, "hoge");
	Val* ns = new_symbol(buf);
	Val* ni = new_integer(56);
	Val* np1 = new_pair(ns, ni);

	Val* np2 = new_pair(np1, &nil);
	val_println(np2);
	val_free(np2);
}


