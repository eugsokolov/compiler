// Eugene Sokolov
// Compilers ECE466
// hash.h

#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct hashItem{
	char *key;
	int isOccupied;
	int isDeleted;
	void *pv;
};

struct hashTable{
	int capacity;
	int filled;
	struct hashItem *data;

};

struct hashTable *hashTable_new(int size);

int insert(struct hashTable *table, char *key, void *pv);

int contains(struct hashTable *table, char *key);

void * getPointer(struct hashTable *table, char *key, int b);

int setPointer(struct hashTable *table, char *key, void *pv);

//int remove(struct hashTable *table, char *key);

int hash(struct hashTable *table, char *key);

int findPos(struct hashTable *table, char *key);

//int rehash(struct hashTable *table);

static unsigned int getPrime(int size);

int hashTable_print(struct hashTable *table);

#endif
