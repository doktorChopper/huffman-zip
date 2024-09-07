#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include <stdbool.h>

typedef struct min_heap_node {
    struct min_heap_node* left;
    struct min_heap_node* right;
    struct min_heap_node* parent;
    unsigned int freq;
    char key;
} min_heap_node_t;

min_heap_node_t* new_min_heap_node(char, unsigned int);

typedef struct {
    unsigned int size;
    unsigned int capacity;
    min_heap_node_t** array;
} min_heap_t;

bool new_min_heap(min_heap_t*);
void free_min_heap(min_heap_t*);
void min_heap_add(min_heap_node_t*, min_heap_t*);
min_heap_node_t* min_heap_extract(min_heap_t*);
void build_min_heap(min_heap_t*);

#endif // _MIN_HEAP_H_
