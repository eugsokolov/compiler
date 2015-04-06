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

struct hashTable * hashTable_new(int size);

int hashTable_insert(struct hashTable *table, char *key, void *pv);

int hashTable_contains(struct hashTable *table, char *key);

void * hashTable_getPointer(struct hashTable *table, char *key, int b);

int hashTable_setPointer(struct hashTable *table, char *key, void *pv);

int hashTable_remove(struct hashTable *table, char *key);

int hashTable_hash(struct hashTable *table, char *key);

int hashTable_findPos(struct hashTable *table, char *key);

//int rehash(struct hashTable *table);

static unsigned int hashTable_getPrime(int size);

int hashTable_print(struct hashTable *table);

#endif
