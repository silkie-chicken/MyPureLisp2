#ifndef INCLUDEGUARD_MYPURELISP_READER
#define INCLUDEGUARD_MYPURELISP_READER

typedef struct token{
	struct token* prev;
	struct token* next;
	char* string;
}Token;

typedef struct {
	Token* head;
	Token* cur;
}Reader;

Token* token_new(char* str);
Token* token_free(Token* t);

Reader* reader_new();
void    reader_free(Reader* r);
char* reader_next(Reader* r);
//char* reader_prev(Reader* r);
char* reader_cur(Reader* r);
char* reader_peepNext(Reader* r);
//char* reader_peepPrev(Reader* r);
void  reader_append(Reader* r, Token* t);
void  reader_peek(Reader* r);

//
int isNum(char c);
int isAlphabet(char c);
Reader* tokenize(char* string);

int skip_whitespace(int pos, char* str);

#endif
