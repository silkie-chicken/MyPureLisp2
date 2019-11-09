#ifndef INCLUDEGUARD_MYPURELISP_READER
#define INCLUDEGUARD_MYPURELISP_READER

typedef struct {
	char** words;
	int    pos;
}Reader;

Reader* tokenize(char* string);

Reader* alloc_reader();

#endif
