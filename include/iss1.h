#ifndef _ISS3_H_
#define _ISS3_H_


#include <stdbool.h>

typedef unsigned int (*hash_func) (char);

typedef struct {
    unsigned int freq;
    unsigned int hash;
    char key;
} huff_node_t;

typedef struct {
    huff_node_t** table;
    unsigned int size;
    unsigned int count;
    hash_func hash_fn;
} iss1_hash_table_t;

typedef struct {
    huff_node_t** array; 
    unsigned int size;
    unsigned int capacity;
} iss1_min_heap_t;

bool new_iss1_hash_table(iss1_hash_table_t*);
bool new_iss1_hash_table_n(iss1_hash_table_t*, unsigned int, hash_func);
void free_iss1_hash_table(iss1_hash_table_t*);
void insert_iss1_hash_table(char, iss1_hash_table_t*);

bool new_iss1_min_heap(iss1_min_heap_t*);
bool new_iss1_min_heap_n(iss1_min_heap_t*, unsigned int);
void free_iss1_min_heap(iss1_min_heap_t*);
huff_node_t* extract_iss1_min_heap(iss1_min_heap_t*);
void insert_iss1_min_heap(iss1_min_heap_t*, huff_node_t*);
void build_iss1_min_heap_from_array_O_nlong(iss1_min_heap_t*, huff_node_t **, unsigned int);

#endif // _ISS3_H_
