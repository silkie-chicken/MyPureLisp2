
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
void* set(HashTable* pHT, char* keyStr, void* pValue);
void* get(HashTable* pHT, char* keyStr);
void* del(HashTable* pHT, char* keyStr);

int hashFunc(int table_size, char* keyStr);

