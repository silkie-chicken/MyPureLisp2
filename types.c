#include <stdlib.h>
#include "types.h"
#include "util.h"

Val* alloc_val(){
	Val* v = (Val*)malloc(sizeof(Val));
	if_null_exit(v, "can't allocate memory in alloc_val()\n");
	v->type = NIL;
	v->val.integer = 0;
}

void free_val(Val* val){
	switch (val->type){
		case NIL:
		case TRUE:
		case INTEGER:
			free(val);
			break;
		case SYMBOL:
			free(val->val.string);
			free(val);
			break;
		case FUNCTION:
			break;
		case PAIR:
			if (val->val.pair->l != NULL) free_val(val->val.pair->l);
			if (val->val.pair->r != NULL) free_val(val->val.pair->r);
			free(val);
			break;
	}
}

//constructor
Val* new_symbol(char *string){
	Val* v = alloc_val();
	v->type = SYMBOL;
	v->val.string = string;
	return v;
}

Val* new_pair(Val* l, Val* r){
	Val* v = alloc_val();
	v->type = PAIR;
	v->val.pair = (Pair*)malloc(sizeof(Pair));
	if_null_exit(v, "can't allocate memory in new_pair\n");
	v->val.pair->l = l;
	v->val.pair->r = r;
	return v;
}

Val* new_integer(int num){
	Val* v = alloc_val();
	v->val.integer = num;
	return v;
}

Val* new_function(){
	Val* v = alloc_val();
	v->type = FUNCTION;
	return v;
}
