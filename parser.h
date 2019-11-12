#ifndef INCLUDEGUARD_MYPURELISP_PARSER
#define INCLUDEGUARD_MYPURELISP_PARSER

//#include <stdio.h>
#include "types.h"
#include "reader.h"

Val* parse(Reader* r);
Val* parse_list(Reader* r);

#endif
