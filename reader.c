#include <string.h>
#include "reader.h"
#include "util.h"

int skip_whitespace(int pos, char* str){
	for(int i=0;;i++){
		char c = str[pos+i];
		if(c == ' '  ||
		   c == '\n' ||
			c == '\t' ||
			c == '\r') continue;
		return i;
	}
}

Token* token_new(char* str){
	Token* t = (Token*)malloc(sizeof(Token));
	if_null_exit(t, "can't allocate memory in token_new()");
	t->prev = t->next = NULL;
	t->string = str;
	return t;
}

Token* token_free(Token* t){
	if (t == NULL) return NULL;
	if (t->string != NULL) free(t->string);
	Token* nt = t->next;
	free(t);
	return nt;
}

Reader* reader_new(){
	Reader* r = (Reader*)malloc(sizeof(Reader));
	if_null_exit(r, "can't allocate memory in reader_new()");
	r->head = r->cur = NULL;
	return r;
}

void reader_free(Reader* r){
	for (Token* c=r->head;c!=NULL;) {
		Token* next = c->next;
		free(c);
		c = next;
	}
	free(r);
}

char* reader_next(Reader* r){
	if_null_exit(r, "can't use NULL in reader_next(arg1)");
	if (r->cur == NULL) return NULL;
	r->cur = r->cur->next;
	if (r->cur == NULL) return NULL;
	return r->cur->string;
}

//char* reader_prev(Reader* r){
//	if_null_exit(r, "can't use NULL in reader_prev(arg1)");
//	if (r->cur == NULL) return NULL;
//	r->cur = r->cur->prev;
//	if (r->cur == NULL) return NULL;
//	return r->cur->string;
//}

char* reader_cur(Reader* r){
	if_null_exit(r, "can't use NULL in reader_cur(arg1)");
	if (r->cur == NULL) return NULL;
	return r->cur->string;
}

char* reader_peepNext(Reader* r){
	if_null_exit(r, "can't use NULL in reader_peepNext(arg1)");
	if (r->cur == NULL || r->cur->next == NULL) return NULL;
	return r->cur->next->string;
}

//char* reader_peepPrev(Reader* r){
//	if_null_exit(r, "can't use NULL in reader_peepPrev(arg1)");
//	if (r->cur == NULL || r->cur->prev == NULL) return NULL;
//	return r->cur->prev->string;
//}

void  reader_append(Reader* r, Token* ts){
	if_null_exit(r, "can't use NULL in reader_append(arg1)");
	if (r->cur  == NULL) r->cur  = ts;
	if (r->head == NULL) {
		r->head = ts; 
		ts->prev = NULL;
		return;
	}
	Token* tail = r->head;
	for (;tail->next != NULL;tail = tail->next);
	tail->next = ts;
	ts->prev = tail;
}

void  reader_peek(Reader* r){
	if_null_exit(r, "can't use NULL in reader_append(arg1)");
	r->cur = r->head;
}

int isNum(char c){
	return ('0' <= c) && (c <= '9');
};

int isAlphabet(char c){
	return (('A' <= c)&&(c <= 'Z')) || (('a' <= c)&&(c <= 'z'));
};

Reader* tokenize(char* string){
	Reader* r = reader_new();	
	int pos = 0;
	for (;;){
		int  i;
		char c;
		char* new_str_entity;
		pos += skip_whitespace(pos, string);
		switch(string[pos]){
			case '(':
			case ')':
			case '\'':
				new_str_entity = (char*)malloc(sizeof(char)*2);
				new_str_entity[0] = string[pos];
				new_str_entity[1] = '\0';
				reader_append(r, token_new(new_str_entity));
				pos++;
				break;
			case '\"':
				i = 1;
				for (;string[pos+i] != '\"';i++);
				i++;
				new_str_entity = (char*)malloc(sizeof(char)*(i+1));
				strncpy(new_str_entity, &(string[pos]), i);
				reader_append(r, token_new(new_str_entity));
				pos+=i;
				break;
			case '\0':
				return r;
			case ';':
				for (;string[pos]!='\n';pos++){
					if (string[pos] == '\0') return r;
				}
				break;
			case '.':
				if(string[pos+1]==' '  ||
					string[pos+1]=='\n' ||
					string[pos+1]=='\t' ||
					string[pos+1]=='\r' ){
					new_str_entity = (char*)malloc(sizeof(char)*2);
					new_str_entity[0] = string[pos];
					new_str_entity[1] = '\0';
					reader_append(r, token_new(new_str_entity));
					pos++;
				};
			default :
				i=0;
				for(;;i++){
					c = string[pos+i];
					if (isAlphabet(c) || isNum(c)  ||
						 c == '!'|| c == '?'||
						 c == '#'|| c == '$'||
						 c == '%'|| c == '&'||
						 c == '='|| c == '~'||
						 c == '^'||
						 c == '['|| c == ']'||
						 c == '{'|| c == '}'||
						 c == '<'|| c == '>'||
						 c == '.'|| c == '_'||
						 c == '*'|| c == '/'||
						 c == '+'|| c == '-') continue;
					break;
				}
				if(i == 0) {pos++; break;}
				new_str_entity = (char*)malloc(sizeof(char)*(i+1));
				strncpy(new_str_entity, &(string[pos]), i);
				reader_append(r, token_new(new_str_entity));
				pos += i;
				break;
		}
	}
}

//Reader* tokenize(char* string){
//	Reader* r = alloc_reader();
//	for(;;){
//		pos += skip_whitespace(pos, string);
//		switch(string[pos]){
//			case '(':
//			case ')':
//			case ';':
//			case '\'':
//				r->words[r->pos] = (char*)malloc(sizeof(char));
//				sprintf(r->words[r->pos], "%c", string[pos]);
//				pos++;
//				break;
//			case '.':
//				if ()
//			default :
//				for(int i=0;;i++){
//				}
//				break;
//		}
//	}
//}


Reader* alloc_reader(){
	Reader* r = (Reader*)malloc(sizeof(Reader));
	if_null_exit(r, "can't allocate alloc_reader()");
	return r;
}


