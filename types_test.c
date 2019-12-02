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

	Env* env = env_new();
	printf ("~~~~env~~~~\n");
	env_println(env);
	env_regist(env, "val1", np2);
	env_regist(env, "val2", np2);
	val_println(env_fetch(env, "val1")); 
	env_println(env);

	val_free(np2);
}


