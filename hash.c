// Eugene Sokolov
// Compilers ECE466
// hash.c

#include "hash.h"

struct hashTable * hashTable_new(int size){
	
	struct hashTable *table;
	if ((table = malloc(sizeof(struct hashTable))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
        	return NULL;
	}
	
	table->capacity = hashTable_getPrime(size);
	table->filled = 0;	
	
	if ((table->data = calloc(table->capacity, sizeof(struct hashItem))) == NULL){
		fprintf(stderr, "Error: malloc: %s\n", strerror(errno));
	        return NULL;
	}

	int i = 0;
	for(i = 0; i < table->capacity; i++){
		table->data[i].isDeleted = TRUE;
		table->data[i].isOccupied = FALSE;
	}

	return table;
}

int hashTable_insert(struct hashTable *table, char *key, void *pv){

/*
	if(((double)filled/capacity) > 0.7){
		if(rehash())
			return 0;
		else
			return 2;
	}
*/

	if(hashTable_contains(table, key) == TRUE)
		return FALSE;
	
	if(table->capacity * 0.7 < table->filled){
		fprintf(stderr, "Hash table about to exceed size..\n");
		exit(1);
	}

	int i = hashTable_hash(table, key) % table->capacity;
	if (i < 0)
		i += table->capacity;

	while(table->data[i].isOccupied == 1){
		i++;
		i %= table->capacity;
	}
	if((table->data[i].isOccupied == FALSE) || (table->data[i].isDeleted == TRUE)){
		table->data[i].key = key;
		table->data[i].isOccupied = TRUE;
		table->data[i].isDeleted = FALSE;
		table->data[i].pv = pv;
		table->filled++;
		return TRUE;
	}

	return FALSE;
}

int hashTable_contains(struct hashTable *table, char *key){

	int i = hashTable_findPos(table, key);
	if (i == -1)
		return FALSE;
	
	return TRUE;
}

void * hashTable_getPointer(struct hashTable *table, char *key, int b){

	int i = hashTable_findPos(table, key);
	if(i == -1){
		b = FALSE;
		return NULL;	
	}

	b = TRUE;
	return table->data[i].pv;
}

int hashTable_setPointer(struct hashTable *table, char *key, void *pv){

	int i = hashTable_findPos(table, key);
	if(i == -1)
		return -1;
	
	table->data[i].pv = pv;
	return 0;
}

int hashTable_remove(struct hashTable *table, char *key){

	int i = hashTable_findPos(table, key);
	if(i == -1)
		return -1;
	
	table->data[i].isDeleted = TRUE;
	return 0;
}

int hashTable_hash(struct hashTable *table, char *key){
	
	int h = 0;
	unsigned int i = 0;

	for(i = 0; i < strlen(key); i++)
		h = h * HASH_PRIME + key[i];

	h %= table->capacity;
	if(h < 0)
		h += table->capacity;

	return h;	
}

int hashTable_findPos(struct hashTable *table, char *key){

	int i = hashTable_hash(table, key) % table->capacity;
	while(table->data[i].isOccupied == TRUE){
		if(table->data[i].key == key && table->data[i].isDeleted == FALSE)
			return i;
		i++;
	}
	return -1;
}

/*
int rehash(struct hashTable *table){

}
*/

static unsigned int hashTable_getPrime(int size){
	
	int primeslist[] = {73, 607, 2221, 10103, 60251, 100109, 104729, 100003, 2000009, 122949829, 472882049, 961748941 };
	int i = 0;

	while(primeslist[i] <= size)
		i++;

	return primeslist[i];
}

int hashTable_print(struct hashTable *table){

	printf("\n----- start of table -----");

	int i = 0;
	for (i = 0; i < table->capacity; i++){
		if (table->data[i].isOccupied == TRUE && table->data[i].isDeleted == FALSE){
        		printf("%s\n", table->data[i].key);
        	}
    	}
        
	printf("----- end of table -----\n");
	
	return 0;
}
