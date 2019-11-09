#include "reader.h"
#include "util.h"

#define MAX_WORD_NUM 24

Reader* tokenize(char* string){
	Reader* r = alloc_reader();
	r->pos = 0;
	for(;;){
		if(string[r->pos] == ' ') continue;
		switch(string[r->pos]){
			case '(':
				r->pos++;
				break;
			case ')':
				r->pos++;
				break;
			case '.':
				break;
			case '\'':
				break;
			default :
				break;
		}
	}
}

Reader* alloc_reader(){
	Reader* r = (Reader*)malloc(sizeof(Reader));
	if_null_exit(r, "can't allocate alloc_reader()");
	return r;
}


