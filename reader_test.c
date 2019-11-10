#include "reader.h"
#include <stdio.h>

int main(void){
	Reader* r = alloc_reader();
	printf("%d\n", r->pos);
}
