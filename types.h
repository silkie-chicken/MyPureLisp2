#ifndef INCLUDEGUARD_MYPURELISP_TYPES
#define INCLUDEGUARD_MYPURELISP_TYPES

#include <stdint.h>
#include "hash.h"

typedef enum {
	//ATOMS
	NIL      = 0x01,
	TRUE     = 0x02, 
	SYMBOL   = 0x04,
	INTEGER  = 0x08,
	FUNCTION = 0x10,
	BUILDIN_FUNCTION = 0x20,

	PAIR     = 0x40
}Type;

struct pair;
struct function;
struct buildin_function;

typedef struct value{;
	Type type;
	union {
		int64_t integer;
		char*   string;
		struct pair*     pair;
		struct function* func;
		struct buildin_function* b_func;
	}val;
}Val;

typedef struct pair{
	Val* l;
	Val* r;
}Pair;

typedef struct env{
	HashTable* functions;
	HashTable* variables;
}Env;

typedef struct function{
	Val* args;
	Val* body;
	Env* env;
}Function;

typedef struct buildin_function{
	Val* (*body)(Val*);
}BuildinFunction;

Val* val_alloc();
void val_free(Val* val);

extern Val nil;// = (Val){NIL,  0};
extern Val t;//   = (Val){TRUE, 0};

Val* new_symbol (char* string);
Val* new_pair   (Val* l, Val* r);
Val* new_integer(int num);
Val* new_function(Val* args, Val* body);
Val* new_buildin_function(Val* (*bf)(Val*));

//Pairじゃない時エラー吐く
Val* val_car(Val* list);
Val* val_cdr(Val* list);

void val_println(Val* v);
void val_print(Val* v, int isBP);

Env* env_new();
void env_regist(Env* env, char* keyStr, Val* val);
Val* env_fetch (Env* env, char* keyStr);
void env_println(Env* env);

#endif

