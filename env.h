#ifndef INCLUDEGUARD_MYPURELISP_ENV
#define INCLUDEGUARD_MYPURELISP_ENV

#include "hash.h"

typedef struct env{
	int table_size;
	HashTable func_plus_val;
}Env;

env_regist(Env env, Val val);
env_delete(Env env, Val val);

#endif
