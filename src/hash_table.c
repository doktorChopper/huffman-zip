#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_CAPACITY 256

static unsigned long hash_table_capacity = HASH_TABLE_CAPACITY;


bool new_hash_table(hash_table_t * table) {

    unsigned int alloc;

    alloc = hash_table_capacity * sizeof(entry_t);

    table->table = (entry_t**) malloc(alloc);
    if(table->table == NULL)
        return false;

    memset(table->table, 0, alloc);

    table->size = 0;
    table->capacity = hash_table_capacity;

    return true;
}

entry_t* new_entry(char key, unsigned int count) {
    entry_t* ret = (entry_t*) malloc(sizeof(entry_t));
    ret->key = key;
    ret->count = count;

    return ret;
}

void free_hash_table(hash_table_t * table) {
    for(unsigned int i = 0; i < table->capacity; ++i)
        if(table->table[i])
            free(table->table[i]);
    free(table->table);
}

void insert_hash_table(char key, hash_table_t * table) {

    unsigned int index;
    index = key % hash_table_capacity;

    if(table->table[index])
        table->table[index]->count++;
    else {
        table->table[index] = new_entry(key, 1);

        ++table->size;
    }
}
