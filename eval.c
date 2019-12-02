#include "eval.h"
#include <stdio.h>
#include <stdlib.h>

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
			if (ast->val.pair->l->type == FUNCTION)printf("hgeohgoehgeohgoeh\n");
			if (ast->val.pair->l->type == BUILDIN_FUNCTION){
				return (*(ast->val.pair->l->val.b_func->body))(ast->val.pair->r);
			}
	}
}


