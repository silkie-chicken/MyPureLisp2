#ifndef INCLUDEGUARD_MYPURELISP_TYPES
#define INCLUDEGUARD_MYPURELISP_TYPES

#include <stdint.h>
#include "env.h"

typedef enum {
	//ATOMS
	NIL      = 0x01,
	TRUE     = 0x02, 
	SYMBOL   = 0x04,
	INTEGER  = 0x08,
	FUNCTION = 0x10,

	PAIR     = 0x20
}Type;

struct pair;
struct function;

typedef struct value{;
	Type type;
	union {
		int64_t integer;
		char*   string;
		struct pair*     pair;
		struct function* func;
	}val;
}Val;

typedef struct pair{
	Val *l;
	Val *r;
}Pair;

typedef struct function{
	Val *args;
	Val *body;
	Env *env;
}Function;

Val* alloc_val();
void free_val(Val* val);

extern Val nil;// = (Val){NIL,  0};
extern Val t;//   = (Val){TRUE, 0};

Val* new_symbol (char *string);
Val* new_pair   (Val* l, Val* r);
Val* new_integer(int num);
Val* new_function();

#endif
