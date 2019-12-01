#include <stdlib.h>
#include "types.h"
#include "util.h"

Val nil = (Val){NIL, 0};
Val t   = (Val){TRUE, 0};
//t   = (Val){NIL, {0}};

Val* val_alloc(){
	Val* v = (Val*)malloc(sizeof(Val));
	if_null_exit(v, "can't allocate memory in val_alloc()\n");
	v->type = NIL;
	v->val.integer = 0;
}

void val_free(Val* val){
	if (val == NULL) return;
	switch (val->type){
		case NIL:
		case TRUE:
			break;
		case INTEGER:
			free(val);
			break;
		case SYMBOL:
			free(val->val.string);
			free(val);
			break;
		case FUNCTION:
			break;
			free(val);
		case PAIR:
			if (val->val.pair->l != NULL) val_free(val->val.pair->l);
			if (val->val.pair->r != NULL) val_free(val->val.pair->r);
			free(val);
			break;
	}
}

//constructor
Val* new_symbol(char *string){
	Val* v = val_alloc();
	v->type = SYMBOL;
	v->val.string = string;
	return v;
}

Val* new_pair(Val* l, Val* r){
	Val* v = val_alloc();
	v->type = PAIR;
	v->val.pair = (Pair*)malloc(sizeof(Pair));
	if_null_exit(v, "can't allocate memory in new_pair\n");
	v->val.pair->l = l;
	v->val.pair->r = r;
	return v;
}

Val* new_integer(int num){
	Val* v = val_alloc();
	v->type = INTEGER;
	v->val.integer = num;
	return v;
}

Val* new_function(Val args, Val body ,Env env){
	Val* v = val_alloc();
	v->type = FUNCTION;
	return v;
}

void val_println(Val* v){
	val_print(v, 1);
	printf("\n");
}

void val_print(Val* v, int isBP){
	if (v == NULL) {
		printf("NULL");
	}
	switch (v->type){
		case NIL:
			printf("NIL");
			break;
		case TRUE:
			printf("T");
			break;
		case SYMBOL:
			printf("%s", v->val.string);
			break;
		case INTEGER:
			printf("%ld", v->val.integer);
			break;
		case FUNCTION:
			printf("FUNCTION");
			break;
		case PAIR:
			if(0){
				printf("(");
				val_print(v->val.pair->l, 1);
				printf(" . ");
				val_print(v->val.pair->r, 1);
				printf(")");
			}else{
				if (isBP) printf("(");
				val_print(v->val.pair->l, 1);
				if (v->val.pair->r->type == PAIR){
					printf(" ");
					val_print(v->val.pair->r, 0);
				}else if(v->val.pair->r->type != NIL){
					printf(" . ");
					val_print(v->val.pair->r, 0);
				}
				if (isBP) printf(")");
			}
			break;
	}
};
