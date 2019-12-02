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
		case BUILDIN_FUNCTION:
			printf("BUILDIN_FUNCTION");
			break;
		case PAIR:
			if(0){ //is all cons cell
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

// fundamental functions
Val* cons (Val* a, Val* b){
}

Env* env_new(){
	Env* env = (Env*)malloc(sizeof(Env));
	if_null_exit(env, "can't allocate memory in env_new()\n");
	env->functions = hashTable_new(10);
	env->variables = hashTable_new(10);
	return env;
}

void env_regist(Env* env, char* keyStr, Val* val){
	if_null_exit(val, "can't use NULL in env_regist(env, val\n");
//	hashTable_set(env->functions, keyStr, (void*)val);
	hashTable_set(env->variables, keyStr, (void*)val);
}

Val* env_fetch(Env* env, char* keyStr){
	if_null_exit(env,    "can't use NULL in env_get(env, _\n");
	if_null_exit(keyStr, "can't use NULL in env_get(_, keyStr\n");
//	hashTable_set(env->functions, keyStr, (void*)val);
	void* val = hashTable_get(env->variables, keyStr);
	if (val == NULL){
		printf("the variable \'%s\' has no value\n", keyStr);
		exit(1);
	}
	return (Val*)val;
}

//ここ特に汚い
void env_println(Env* env){
	node_t** arr = env->variables->nodes;
	int size = env->variables->size;
	for (int i=0;i<size;i++){
		for (node_t* c = arr[i];c!=NULL;c = c->pNextNode){
			printf("symbal \'%s\' : ", c->keyStr);
			val_print((Val*)(c->pValue), 1);
			printf("\n");
		}
	}
}

