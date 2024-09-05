#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 256

static unsigned long default_hash_table_size = DEFAULT_SIZE;

static unsigned long default_hash_func(char);

static unsigned long default_hash_func(char key) {
    return key % default_hash_table_size;
}


bool new_hash_table(hash_table_t * table) {
    return new_hash_table_n(table, default_hash_table_size, default_hash_func);
}

bool new_hash_table_n(hash_table_t * table, unsigned long size, hash_func hash_fn) {
    unsigned long alloc = size * sizeof(hash_table_t);

    table->table = (entry_t**) malloc(alloc);
    if(table->table == NULL)
        return false;

    memset(table->table, 0, alloc);

    table->size = size;
    table->count = 0;
    table->hash_fn = hash_fn;
    return true;
}

void insert_hash_table(hash_table_t * table, char key) {
    unsigned long index;

    entry_t* ent = (entry_t*) malloc(sizeof(entry_t));
    ent->key = key;
    ent->hash = table->hash_fn(key);
    index = ent->hash % default_hash_table_size;

    table->table[ent->hash] = ent;
    table->count++;
}

void free_hash_table(hash_table_t * table) {
    
    for(unsigned int i = 0; i < table->size; ++i)
        if(table->table[i] != NULL)
            free(table->table[i]);

    free(table->table);
}


