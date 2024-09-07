#include "../include/min_heap.h"
#include <stdlib.h>
#include <string.h>

#define MIN_HEAP_CAPACITY 256

static unsigned int min_heap_capacity = MIN_HEAP_CAPACITY;

static inline unsigned int left_child_idx(unsigned int);
static inline unsigned int right_child_idx(unsigned int);
static inline unsigned int parent_idx(unsigned int);
static void sift_up(int, min_heap_t*);
static void sift_down(int, min_heap_t*);

static inline unsigned int left_child_idx(unsigned int i) {
    return 2 * i + 1;
}

static inline unsigned int right_child_idx(unsigned int i) {
    return 2 * i + 1;
}

static inline unsigned int parent_idx(unsigned int i) {
    return (i - 1) / 2;
}

static void sift_up(int i, min_heap_t* minheap) {

    min_heap_node_t* swp = 0;

    while(i > 0 && minheap->array[parent_idx(i)] > minheap->array[i]) {
        swp = minheap->array[i]; 
        minheap->array[i] = minheap->array[parent_idx(i)];
        minheap->array[parent_idx(i)] = swp;
        i = parent_idx(i);
    }
}

static void sift_down(int i, min_heap_t* minheap) {
    int min_child;
    min_heap_node_t* swp;

    if(left_child_idx(i) < minheap->size - 1 && minheap->array[left_child_idx(i)] < minheap->array[i])
        min_child = left_child_idx(i);
    else
        min_child = i;

    if(right_child_idx(i) < minheap->size - 1 && minheap->array[right_child_idx(i)] < minheap->array[min_child])
        min_child = right_child_idx(i);

    if(min_child != i) {
        swp = minheap->array[min_child];
        minheap->array[min_child] = minheap->array[i];
        minheap->array[i] = swp;
        sift_down(min_child, minheap);
    }
}

min_heap_node_t* new_min_heap_node(char key, unsigned int freq) {
    min_heap_node_t* ret;

    ret = (min_heap_node_t*) malloc(sizeof(min_heap_node_t));
    ret->freq = freq;
    ret->key = key;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

bool new_min_heap(min_heap_t * minheap) {

    unsigned int alloc;
    alloc = min_heap_capacity * sizeof(unsigned int);
    minheap->array = (min_heap_node_t**) malloc(alloc);
    if(minheap->array == NULL)
        return false;

    memset(minheap->array, 0, alloc);

    minheap->size = 0;
    minheap->capacity = min_heap_capacity;

    return true;
}

void free_min_heap(min_heap_t * minheap) {
    for(unsigned int i = 0; i < minheap->size; ++i)
        free(minheap->array[i]);
    free(minheap->array);
}

void min_heap_add(min_heap_node_t* val, min_heap_t * minheap) {
    int i = minheap->size;
    ++minheap->size;

    while(i > 0 && val->freq < minheap->array[parent_idx(i)]->freq) {
        minheap->array[i] = minheap->array[parent_idx(i)];
        i = parent_idx(i);
    }
    minheap->array[i] = val; 
}

min_heap_node_t* min_heap_extract(min_heap_t * minheap) {
    min_heap_node_t* ret;
    if(minheap->size == 0)
        return NULL;

    ret = minheap->array[0];

    minheap->array[0] = minheap->array[minheap->size - 1];
    minheap->size--;

    sift_down(0, minheap);
    return ret;
}

void build_min_heap(min_heap_t * minheap) {
    for(unsigned int i = minheap->size / 2; i > 0; --i)
        sift_down(i, minheap);
}

