#ifndef INCLUDEGUARD_MYPURELISP_HASH 
#define INCLUDEGUARD_MYPURELISP_HASH 

typedef struct node{
	char*        keyStr;
	void*        pValue;
	struct node* pNextNode; 
}node_t;

typedef struct {
	node_t** nodes;
	int size;
	int keyStr_len;
}HashTable;

HashTable* newHashTable(int table_size, int keyStr_len);
//return old value
void* set(HashTable* pHT, char* keyStr, void* pValue);
void* get(HashTable* pHT, char* keyStr);
//return old value
void* del(HashTable* pHT, char* keyStr);

int hashFunc(int table_size, char* keyStr);

#endif
