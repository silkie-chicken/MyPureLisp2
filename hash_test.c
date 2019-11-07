#include <stdio.h>
#include <string.h>
#include "hash.h"

int main(void){
	printf("hashFunc: %d\n", hashFunc(20, "hogera"));
	printf("hashFunc: %d\n", hashFunc(20, "hogdsa"));

	HashTable* ht = newHashTable(20, 20);
	int u = (long int)set(ht, "hogera", (void*)1919);
	printf("val: %d\n", u);
	set(ht, "hogdsa", (void*)810);
	set(ht, "eripse", (void*)514);
	int v = (long int)get(ht, "hogdsa");
	printf("get val: %d\n", v);
	int w = (long int)get(ht, "eripse");
	printf("get val: %d\n", w);
	int x = (long int)del(ht, "hogdsa");
	printf("del val: %d\n", x);
	int y = (long int)get(ht, "hogdsa");
	printf("get : %d\n", y);
	int z = (long int)del(ht, "hogdsa");
	printf("del val: %d\n", z);

	return 0;
}
