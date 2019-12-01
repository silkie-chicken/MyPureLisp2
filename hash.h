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
}HashTable;

HashTable* hashTable_new(int table_size);
//return old value
void* hashTable_set(HashTable* pHT, char* keyStr, void* pValue);
void* hashTable_get(HashTable* pHT, char* keyStr);
//return old value
void* hashTable_del(HashTable* pHT, char* keyStr);

int hashFunc(int table_size, char* keyStr);

#endif
