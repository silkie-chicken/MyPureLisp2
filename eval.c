#include "eval.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Val* quote(Val* args){
	if (args->type != PAIR){
		printf("なんでcons cell使うんですか???? どうして…\n");
		exit(1);
	}
	return args->val.pair->l;
}

Val* cond(Val* args,Env* env){
	for (Val* cur=args; cur->type!=NIL; cur=cur->val.pair->r){
		if (cur->type != PAIR){
			printf("only list can be executed\n");
			exit(1);
		}
		if (cur->val.pair->l->type != PAIR){
			printf("only list can be used in cond\n");
			exit(1);
		}
		if (eval(cur->val.pair->l->val.pair->l, env)->type != NIL){
			if (cur->val.pair->l->val.pair->r->type != PAIR) return &t;
			return eval(cur->val.pair->l->val.pair->r->val.pair->l, env); 
		}
	}
	return &nil;
}

//(lambda (x) (* x x))
//((x) . ((* x x) . nil)))
//(lambda () 3)
//(() . (3 . nil)))
Val* lambda(Val* args){
	if (args->type != PAIR) {
		printf("too few args in lambda\n");
		exit(1);
	}
	Val* a = args->val.pair->l;
	if (args->val.pair->r->type != PAIR) {
		printf("too few args in lambda\n");
		exit(1);
	}
	Val* b = args->val.pair->r->val.pair->l;
	if (args->val.pair->r->type != PAIR){
		printf("too few args in lambda\n");
		exit(1);
	}
	return new_function(a, b);
}

Val* define(Val* args, Env* env){
	if (args->type != PAIR || args->val.pair->l->type != SYMBOL || args->val.pair->r->type != PAIR){
		printf("後で考えるin define\n");
		exit(1);
	}
	
	char* key = args->val.pair->l->val.string; 
	Val* val = eval(args->val.pair->r->val.pair->l, env);
	env_regist(env, key, val);
	return val;
}

//どこで折った枝の実体を消すのか?
Val* eval(Val* ast, Env* env){
	switch(ast->type){
		case NIL:
		case TRUE:
		case INTEGER:
		case FUNCTION:
		case BUILDIN_FUNCTION:
			return ast;
		case SYMBOL:
			return env_fetch(env, ast->val.string);
		case PAIR:
			//specialform
			if (ast->val.pair->l->type == SYMBOL){
				if (strcmp(ast->val.pair->l->val.string, "quote") == 0){       return quote (ast->val.pair->r);
				}else if (strcmp(ast->val.pair->l->val.string, "cond") == 0){  return cond  (ast->val.pair->r, env);
				}else if (strcmp(ast->val.pair->l->val.string, "lambda") == 0){return lambda(ast->val.pair->r);
				}else if (strcmp(ast->val.pair->l->val.string, "define") == 0){return define(ast->val.pair->r, env);
				}
			}

			//eval list
			ast->val.pair->l = eval(ast->val.pair->l, env);
			if(!(ast->val.pair->l->type & (FUNCTION | BUILDIN_FUNCTION))){
				val_print(ast->val.pair->l, 1);
				printf(" is not a function\n");
				exit(1);
			}
			for (Val* cur=ast->val.pair->r; cur->type!=NIL; cur=cur->val.pair->r){
				if (cur->type != PAIR){
					printf("only list can be executed\n");
					exit(1);
				}
				cur->val.pair->l = eval(cur->val.pair->l ,env);
			}
			if (ast->val.pair->l->type == FUNCTION){
				Val* cur_args = ast->val.pair->r;
				Val* cur_keys = ast->val.pair->l->val.func->args;
				for (;;){
					if ((cur_args->type != PAIR) || (cur_keys->type != PAIR)) break;
					if (cur_keys->val.pair->l->type != SYMBOL){
						printf("ひきすうにしんぼるいがいつかうな定期\n");
						exit(1);
					}
					env_regist(env, cur_keys->val.pair->l->val.string, cur_args->val.pair->l);
					cur_args = cur_args->val.pair->r;
					cur_keys = cur_keys->val.pair->r;
				}
				return eval(ast->val.pair->l->val.func->body, env);
			}
			if (ast->val.pair->l->type == BUILDIN_FUNCTION){
				return (*(ast->val.pair->l->val.b_func->body))(ast->val.pair->r);
			}
	}
}


