#include <string.h>
#include "types.h"
#include "reader.h"
#include "util.h"

Val* parse(Reader* r){
	char* str = reader_cur(r);

	if (strcmp(")", str) == 0){
		return 
	}else if (strcmp("(", str) == 0){
	}else if (strcmp("hoge", str) == 0){
	}else{
		new_integer(210);
		return 
	}
}



