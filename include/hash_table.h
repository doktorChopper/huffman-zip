#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <stdbool.h>

typedef unsigned long (*hash_func) (char);

typedef struct entry {
    char key;    
    unsigned long hash;
} entry_t;


typedef struct {
    entry_t** table;
    unsigned long size;
    hash_func hash_fn;
    unsigned long count;
} hash_table_t;

bool new_hash_table(hash_table_t*);
bool new_hash_table_n(hash_table_t*, unsigned long, hash_func);
void insert_hash_table(hash_table_t*, char);
void free_hash_table(hash_table_t*);

#endif // _HASH_TABLE_
