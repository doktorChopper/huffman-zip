#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <stdbool.h>

typedef struct entry {
    char key;
    unsigned int count;
} entry_t;

entry_t* new_entry(char, unsigned int);

typedef struct {
    entry_t** table;
    unsigned int size;
    unsigned int capacity;
} hash_table_t;

bool new_hash_table(hash_table_t*);
void free_hash_table(hash_table_t*);
void insert_hash_table(char, hash_table_t*);

#endif // _HASH_TABLE_
