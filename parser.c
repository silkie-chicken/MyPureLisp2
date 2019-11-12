#include <string.h>
#include "types.h"
#include "parser.h"
#include "reader.h"
#include "util.h"

int isInteger(char* str){
	int n = atoi(str);
	if (n == 0 || strcmp(str, "0") == 0) return 0;
	return 1;
}

Val* parse(Reader* r){
	char* str = reader_cur(r);

	if (strcmp("(", str) == 0){
		reader_next(r);
		return parse_list(r);
	}else if (strcmp(")", str) == 0){
		return NULL;
	}else if (strcmp("nil", str) == 0){
		return &nil;
	}else if (strcmp("t", str) == 0){
		return &t;
	}else if (strcmp("'", str) == 0){
		reader_next(r);
		return new_pair(new_symbol("quote"), new_pair(parse(r), &nil));
	}else if (isInteger(str)){
		return new_integer(atoi(str));
	}else{
		return new_symbol(str);
	}
}

Val* parse_list(Reader* r){
	Val* ln = parse(r);
//	printf("%s ", reader_cur(r));
	if (ln == NULL){
		return &nil;
	}
	reader_next(r);
	return new_pair(ln, parse_list(r));
}

