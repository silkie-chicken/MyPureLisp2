#ifndef INCLUDEGUARD_MYPURELISP_READER
#define INCLUDEGUARD_MYPURELISP_READER

typedef struct token{
	struct token* prev;
	struct token* next;
	char* string;
}Token;

typedef struct {
	Token* head;
	Token* tail;
	Token* cur;
}Reader;

void token_new(char* str);
void token_free(Token* token);

Reader* reader_new();
void    reader_free();
char* reader_next(Reader* r);
char* reader_prev(Reader* r);
char* reader_cur(Reader* r);
char* reader_peepNext(Reader* r);
char* reader_peepPrev(Reader* r);
void  reader_append(Reader* r, Token* ts);

//
Reader* tokenize(char* string);

int skip_whitespace(int pos, char* str);

#endif
