#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hashFunc(int table_size, char* keyStr){
	int sum = 0;
	
	for (int i=0; keyStr[i] != '\0'; i++) sum += keyStr[i];
	return sum % table_size;
}

node_t* newNode(char* keyStr, int keyStr_len, void* p){
	node_t* n = (node_t*)malloc(sizeof(node_t));
	if (n == NULL){
		perror("can't allocate memory of hash table's node\n");
		exit(1);
	}
	n->keyStr = (char*)malloc(sizeof(char)*keyStr_len);
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

HashTable* newHashTable(int table_size, int keyStr_len){
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	if (h == NULL){
		perror("can't allocate memory of hashtable\n");
		exit(1);
	}
	h->size        = table_size;
	h->keyStr_len  = keyStr_len;
	h->nodes       = (node_t**)malloc(sizeof(node_t*)*table_size);
	if (h->nodes == NULL){
		perror("can't allocate memory of hashtable->nodes\n");
		exit(1);
	}
	for (int i=0; i<table_size; i++) h->nodes[i] = NULL;
	return h;
}

void* set(HashTable* pHT, char* keyStr, void* pValue){
	int n =  hashFunc(pHT->size, keyStr);
	if (pHT->nodes[n] == NULL){
		int len = strlen(keyStr);
		if (len > pHT->keyStr_len){
			perror("too long key string\n");
			exit(1);
		}
		pHT->nodes[n] = newNode(keyStr, len, pValue);
		return NULL;
	}
}

void* get(HashTable* pHT, char* keyStr){
	int n = hashFunc(pHT->size, keyStr);
	if (pHT->nodes[n] != NULL){
		return pHT->nodes[n]->pValue;
	}
	return NULL;
}

