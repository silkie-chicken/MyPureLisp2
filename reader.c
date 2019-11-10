#include "reader.h"
#include "util.h"

int skip_whitespace(int pos, char* str){
	for(int i=0;;i++){
		char c = str[pos];
		if(c == ' '  ||
		   c == '\n' ||
			c == '\t' ||
			c == '\r') continue;
		return i;
	}
}

Reader* tokenize(char* string){
	Reader* r = alloc_reader();
	for(;;){
		pos += skip_whitespace(pos, string);
		switch(string[pos]){
			case '(':
			case ')':
			case ';':
			case '\'':
				r->words[r->pos] = (char*)malloc(sizeof(char));
				sprintf(r->words[r->pos], "%c", string[pos]);
				pos++;
				break;
			case '.':
				if ()
			default :
				for(int i=0;;i++){
				}
				break;
		}
	}
}


Reader* alloc_reader(){
	Reader* r = (Reader*)malloc(sizeof(Reader));
	if_null_exit(r, "can't allocate alloc_reader()");
	return r;
}


