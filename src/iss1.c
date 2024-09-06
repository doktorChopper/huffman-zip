#include "../include/iss1.h"
#include "stdlib.h"
#include <c++/12/string_view>
#include <string.h>

#define DEFAULT_HASH_TABLE_SIZE 256
#define DEFAULT_MIN_HEAP_CAPACITY 256

static const unsigned int default_hash_table_size = DEFAULT_HASH_TABLE_SIZE;
static const unsigned int default_min_heap_capacity = DEFAULT_MIN_HEAP_CAPACITY;

static unsigned int default_hash_func(char);
static void sift_up(unsigned int, iss1_min_heap_t*);
static void sift_down(unsigned int, iss1_min_heap_t*);

static inline unsigned int left_child_idx(unsigned int);
static inline unsigned int right_child_idx(unsigned int);
static inline unsigned int parent_idx(unsigned int);

static inline unsigned int left_child_idx(unsigned int index) {
    return 2 * index + 1;
}

static inline unsigned int right_child_idx(unsigned int index) {
    return 2 * index + 2;
}

static inline unsigned int parent_idx(unsigned int index) {
    return (index - 1) / 2;
}

static void sift_up(unsigned int index, iss1_min_heap_t* min_heap) {

    huff_node_t* swp;

    while(index > 0 && min_heap->array[index]->freq < min_heap->array[parent_idx(index)]->freq) {
    
        swp = min_heap->array[index];
        min_heap->array[index] = min_heap->array[parent_idx(index)]; 
        min_heap->array[parent_idx(index)] = swp;

        index = parent_idx(index);
    }
}

static void sift_down(unsigned int index, iss1_min_heap_t* min_heap){
    unsigned int min_child;
    huff_node_t* swp;

    if(left_child_idx(index) < min_heap->size - 1 && min_heap->array[left_child_idx(index)] < min_heap->array[index])
        min_child = left_child_idx(index);

    if(right_child_idx(index) < min_heap->size - 1 && min_heap->array[right_child_idx(index)] < min_heap->array[min_child])
        min_child = right_child_idx(index);

    if(min_child != index) {

        swp = min_heap->array[min_child]; 
        min_heap->array[min_child] = min_heap->array[index];
        min_heap->array[index] = swp;

        sift_down(min_child,min_heap);
    }
}

static unsigned int default_hash_func(char c) {
    return c % default_hash_table_size;
}


bool new_iss1_hash_table_n(iss1_hash_table_t * table, unsigned int size, hash_func hash_fn) {
    unsigned int alloc;

    alloc = size * sizeof(huff_node_t);

    table->table = (huff_node_t**) malloc(alloc); 
    if(table->table == NULL)
        return false;

    memset(table->table, 0, alloc);

    table->size = size;
    table->count = 0;
    table->hash_fn = hash_fn; 
    return true;
}

bool new_iss1_hash_table(iss1_hash_table_t * table) {
    return new_iss1_hash_table_n(table, default_hash_table_size, default_hash_func);
}

void insert_iss1_hash_table(char key, iss1_hash_table_t * table) {
    unsigned int index;
    unsigned int hash;

    hash = table->hash_fn(key);
    index = hash % default_hash_table_size;

    if(table->table[index])
        table->table[index]->freq++;
    else {
        huff_node_t* ent = (huff_node_t*) malloc(sizeof(huff_node_t));

        ent->key = key;
        ent->freq = 1;
        ent->hash = hash;

        table->table[index] = ent;
        table->count++;
    }

}

void free_iss1_hash_table(iss1_hash_table_t * table) {
    
    for(unsigned int i = 0; i < table->size; ++i) 
        if(table->table[i])
            free(table->table[i]);

}


bool new_iss1_min_heap(iss1_min_heap_t * min_heap) {
       return new_iss1_min_heap_n(min_heap, default_min_heap_capacity); 
}

bool new_iss1_min_heap_n(iss1_min_heap_t * min_heap, unsigned int capacity) {
    unsigned int alloc;

    alloc = capacity * sizeof(huff_node_t);

    min_heap->array = (huff_node_t**) malloc(alloc);
    if(min_heap->array == NULL)
        return false;

    memset(min_heap->array, 0, alloc);

    min_heap->capacity = capacity;
    min_heap->size = 0;

    return true;

}

void free_iss1_min_heap(iss1_min_heap_t * min_heap) {

    for(unsigned int i = 0; i < min_heap->size; ++i)
        free(min_heap->array[i]);
}


void insert_iss1_min_heap(iss1_min_heap_t * min_heap, huff_node_t * huff_node) {

    min_heap->array[min_heap->size] = huff_node;

    if(min_heap->size == min_heap->capacity) {
        min_heap->array = (huff_node_t**) realloc(min_heap->array, 2 * min_heap->capacity * sizeof(huff_node_t));
        min_heap->capacity = 2 * min_heap->capacity;
    }

    sift_up(min_heap->size, min_heap);
    min_heap->size++;
}

void build_iss1_min_heap_from_array_O_nlong(iss1_min_heap_t* min_heap, huff_node_t ** array, unsigned int size) {

    new_iss1_min_heap_n(min_heap, size);

    for(unsigned int i = 0; i < size; ++i)
        if(array[i])
            insert_iss1_min_heap(min_heap, array[i]); 
}
