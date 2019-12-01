#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hashFunc(int table_size, char* keyStr){
	int sum = 0;
	
	for (int i=0; keyStr[i] != '\0'; i++) sum += keyStr[i];
	return sum % table_size;
}

node_t* newNode(char* keyStr, void* p){
	node_t* n = (node_t*)malloc(sizeof(node_t));
	if (n == NULL){
		perror("can't allocate memory of hash table's node\n");
		exit(1);
	}
	int len = strlen(keyStr)+1;
	n->keyStr = (char*)malloc(sizeof(char)*len);
	if (n == NULL){
		perror("can't allocate memory of hashtable's node->keyStr\n");
		exit(1);
	}
	strcpy(n->keyStr, keyStr);
	n->pValue    = p;
	n->pNextNode = NULL;
	return n;
}

void freeNode(node_t* n){
	if (n == NULL) return;
	if (n->keyStr != NULL) free(n->keyStr);
	free (n);
}

HashTable* hashTable_new(int table_size){
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	if (h == NULL){
		perror("can't allocate memory of hashtable\n");
		exit(1);
	}
	h->size        = table_size;
	h->nodes       = (node_t**)malloc(sizeof(node_t*)*table_size);
	if (h->nodes == NULL){
		perror("can't allocate memory of hashtable->nodes\n");
		exit(1);
	}
	for (int i=0; i<table_size; i++) h->nodes[i] = NULL;
	return h;
}

void* hashTable_set(HashTable* pHT, char* keyStr, void* pValue){
	int k =  hashFunc(pHT->size, keyStr);

	node_t* n = pHT->nodes[k];
	if (n == NULL){
		pHT->nodes[k] = newNode(keyStr, pValue);
		return NULL;
	}
	for (;;){
		if (strcmp(n->keyStr, keyStr) == 0){
			void* old = n->pValue;
			n->pValue = pValue;
			return old;
		}
		if (n->pNextNode == NULL){
			n->pNextNode = newNode(keyStr, pValue);
			return NULL;
		}
		n = n->pNextNode;
	}
}

void* hashTable_get(HashTable* pHT, char* keyStr){
	int k = hashFunc(pHT->size, keyStr);
	for (node_t* n=pHT->nodes[k]; n!=NULL; n = n->pNextNode){
		if (strcmp(n->keyStr, keyStr) == 0) return n->pValue;
	}
	return NULL;
}

void* hashTable_del(HashTable* pHT, char* keyStr){
	int k = hashFunc(pHT->size, keyStr);
	node_t* n = pHT->nodes[k];
	if (n == NULL) return NULL;
	if (strcmp(n->keyStr, keyStr) == 0){
		void* vp = n->pValue;
		pHT->nodes[k] = n->pNextNode;
		freeNode(n);
		return vp;
	}
	for (; n->pNextNode != NULL; n = n->pNextNode){
		if (strcmp(n->pNextNode->keyStr, keyStr) != 0) continue;
		void* vp = n->pNextNode->pValue;
		node_t* tmp = n->pNextNode->pNextNode;
		freeNode(n->pNextNode);
		n->pNextNode = tmp;
		return vp;
	} 
	return NULL;
}

