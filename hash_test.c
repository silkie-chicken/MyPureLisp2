#include <stdio.h>
#include <string.h>
#include "hash.h"

int main(void){
	char buf[20] = "hogehoge";
	printf("str: %s\n", buf);
	printf("return: %d\n", hashFunc(20, buf));

	HashTable* ht = newHashTable(20, 20);
	set(ht, "hgoei", (void*)324);
	int v = (long int)get(ht, "hgoei");
	printf("val: %d\n", v);
	
	return 0;
}
