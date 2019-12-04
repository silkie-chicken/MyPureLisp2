#include <stdlib.h>
#include <string.h>
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

Val* new_function(Val* args, Val* body){
	Val* v = val_alloc();
	v->type = FUNCTION;
	v->val.func = (Function*)malloc(sizeof(Function));
	v->val.func->args = args;
	v->val.func->body = body;
//	v->val.func->env  = env;
	return v;
}

Val* new_buildin_function(Val* (*bf)(Val*)){
	Val* v = val_alloc();
	v->type = BUILDIN_FUNCTION;
	v->val.b_func = (BuildinFunction*)malloc(sizeof(BuildinFunction));
	if_null_exit(v->val.b_func, "can't allocate memory in new_buildin_function\n");
	v->val.b_func->body = bf;
	return v;
}

Val* val_car(Val* list){
	if (list->type != PAIR || list->type != NIL) return NULL;
	return list->val.pair->l;
}

Val* val_cdr(Val* list){
	if (list->type != PAIR || list->type != NIL) return NULL;
	return list->val.pair->r;
}

//第二引数から始まるリストの全要素に関数を適用し，新しいリストを返す
//渡す関数に可能な限り新しい値を返すことを期待する
Val* mapcar(Val* (*func)(Val*), Val* list){
	if (list->type == NIL) return &nil;
	Val* bp = new_pair(&nil, &nil);

	Val** d = &(bp->val.pair->l);
	for(Val* cur=list; list->type != NIL; cur = val_cdr(cur)){
		if (list->type != PAIR) return NULL; //リストでは無かった
		*d = new_pair((*func)(val_car(cur)), &nil);
		d  = &((*d)->val.pair->r);
	}
	return bp;
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
			printf("#<FUNCTION :LAMBDA ");
			val_print(v->val.func->args, 1);
			printf(" ");
			val_print(v->val.func->body, 1);
			printf(">");
			break;
		case BUILDIN_FUNCTION:
			printf("#<BUILDIN_FUNCTION なんか>");
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
Val* fundamental_car(Val* l){
	if (l->type != PAIR){
		printf("too few args in car\n");
		exit(1);
	}
	if (l->val.pair->l->type == PAIR) return l->val.pair->l->val.pair->l;
	if (l->val.pair->l->type == NIL)  return l->val.pair->l;
	//エラー処理は適当
	val_print(l, 1);
	printf(" is not a list\n");
	exit(1);
}

Val* fundamental_cdr(Val* l){
	if (l->type != PAIR){
		printf("too few args in cdr\n");
		exit(1);
	}
	if (l->val.pair->l->type == PAIR) return l->val.pair->l->val.pair->r;
	if (l->val.pair->l->type == NIL)  return l->val.pair->l;
	//エラー処理は適当
	val_print(l, 1);
	printf(" is not a list\n");
	exit(1);
}

Val* fundamental_cons(Val* l){
	if (l->type != PAIR) printf("too few args in cons\n");
	if (l->val.pair->r->type != PAIR) printf("too few args in cons\n");
	return new_pair(l->val.pair->l, l->val.pair->r->val.pair->l);
}

Val* fundamental_atom(Val* l){
	if (l->val.pair->l->type == PAIR) return &nil;
	return &t;
}

Val* fundamental_eq(Val* l){
	if (l->type != PAIR) printf("too few args in eq\n");
	Val* v1 = l->val.pair->l;
	if (l->val.pair->r->type != PAIR) printf("too few args in eq\n");
	Val* v2 = l->val.pair->r->val.pair->l;
	if (v1->type != v2->type) return &nil;
	switch (v1->type){
		case NIL:
			break;
		case TRUE:
			break;
		case INTEGER:
			if (v1->val.integer != v2->val.integer) return &nil;
			break;
		case SYMBOL:
			if (strcmp(v1->val.string, v2->val.string) != 0) return &nil;
			break;
		case BUILDIN_FUNCTION:
			if (v1->val.b_func != v2->val.b_func) return &nil;
			break;
		case FUNCTION:
		//TODO
			break;
	}
	return &t;
}

Val* fundamental_plus(Val* l){
	int acc=0;
	for (Val* cur = l; cur->type == PAIR; cur = cur->val.pair->r){
		if(cur->val.pair->l->type != INTEGER){
			printf("only integer can be used in plus\n");
			exit(0);
		}
		acc += cur->val.pair->l->val.integer;
	}
	return new_integer(acc);
}

Val* fundamental_minus(Val* l){
	if (l->type != PAIR || l->val.pair->l->type != INTEGER){
		printf("too few or invalid args in minus\n");
		exit(1);
	}
	int acc = l->val.pair->l->val.integer;
	if (l->val.pair->r->type != PAIR) return new_integer(-acc);
	for (Val* cur = l->val.pair->r; cur->type == PAIR; cur = cur->val.pair->r){
		if(cur->val.pair->l->type != INTEGER){
			printf("only integer can be used in minus\n");
			exit(0);
		}
		acc -= cur->val.pair->l->val.integer;
	}
	return new_integer(acc);
}

Val* fundamental_mul(Val* l){
	int acc=1;
	for (Val* cur = l; cur->type == PAIR; cur = cur->val.pair->r){
		if(cur->val.pair->l->type != INTEGER){
			printf("only integer can be used in mul\n");
			exit(0);
		}
		acc *= cur->val.pair->l->val.integer;
	}
	return new_integer(acc);
}

//TODO div zero
Val* fundamental_div(Val* l){
	if (l->type != PAIR || l->val.pair->l->type != INTEGER){
		printf("too few or invalid args in div\n");
		exit(1);
	}
	int acc = l->val.pair->l->val.integer;
	if (l->val.pair->r->type != PAIR) return new_integer(1/acc);
	for (Val* cur = l->val.pair->r; cur->type == PAIR; cur = cur->val.pair->r){
		if(cur->val.pair->l->type != INTEGER){
			printf("only integer can be used in div\n");
			exit(0);
		}
		acc /= cur->val.pair->l->val.integer;
	}
	return new_integer(acc);
}

Env* env_new(){
	Env* env = (Env*)malloc(sizeof(Env));
	if_null_exit(env, "can't allocate memory in env_new()\n");
	env->functions = hashTable_new(10);
	env->variables = hashTable_new(10);
	env_regist(env, "car", new_buildin_function(fundamental_car));//new_buildin_function(fundamental_car));
	env_regist(env, "cdr", new_buildin_function(fundamental_cdr));//new_buildin_function(fundamental_car));
	env_regist(env, "cons", new_buildin_function(fundamental_cons));//new_buildin_function(fundamental_car));
	env_regist(env, "eq", new_buildin_function(fundamental_eq));//new_buildin_function(fundamental_car));
	env_regist(env, "atom", new_buildin_function(fundamental_atom));//new_buildin_function(fundamental_car));
	//これはついで
	env_regist(env, "+", new_buildin_function(fundamental_plus));//new_buildin_function(fundamental_car));
	env_regist(env, "-", new_buildin_function(fundamental_minus));//new_buildin_function(fundamental_car));
	env_regist(env, "*", new_buildin_function(fundamental_mul));//new_buildin_function(fundamental_car));
	env_regist(env, "/", new_buildin_function(fundamental_div));//new_buildin_function(fundamental_car));
	return env;
}

void env_regist(Env* env, char* keyStr, Val* val){
	if_null_exit(env,    "can't use NULL in env_regist(env, keyStr, val\n");
	if_null_exit(keyStr, "can't use NULL in env_regist(env, keyStr, val\n");
	if_null_exit(val,    "can't use NULL in env_regist(env, keyStr, val\n");
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

