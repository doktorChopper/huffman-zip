#include "../include/min_heap.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 11

static unsigned int default_min_heap_capacity = DEFAULT_CAPACITY;

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

    unsigned int tmp = 0;

    while(i > 0 && minheap->array[parent_idx(i)] > minheap->array[i]) {
        tmp = minheap->array[i]; 
        minheap->array[i] = minheap->array[parent_idx(i)];
        minheap->array[parent_idx(i)] = tmp;
        i = parent_idx(i);
    }
}

static void sift_down(int i, min_heap_t* minheap) {
    int min_child;

    if(left_child_idx(i) < minheap->size - 1 && minheap->array[left_child_idx(i)] < minheap->array[i])
        min_child = left_child_idx(i);

    if(right_child_idx(i) < minheap->size - 1 && minheap->array[right_child_idx(i)] < minheap->array[min_child])
        min_child = right_child_idx(i);

    if(min_child != i) {
        unsigned int tmp = minheap->array[min_child];
        minheap->array[min_child] = minheap->array[i];
        minheap->array[i] = tmp;
        sift_down(min_child, minheap);
    }
}

bool new_min_heap(min_heap_t * minheap) {

    unsigned int alloc;
    alloc = default_min_heap_capacity * sizeof(unsigned int);
    minheap->array = malloc(alloc);
    if(minheap->array == NULL)
        return false;

    memset(minheap->array, 0, alloc);

    minheap->size = 0;
    minheap->capacity = default_min_heap_capacity;

    return true;
}

void min_heap_add(unsigned int val, min_heap_t * minheap) {

    minheap->array[minheap->size] = val;
    minheap->size++;

    if(minheap->size == minheap->capacity){
        minheap->array = (unsigned int*) realloc(minheap->array, 2 * minheap->capacity);
        minheap->capacity = 2 * minheap->capacity;
    }
    sift_up(minheap->size, minheap);
}

unsigned int min_heap_extract(min_heap_t * minheap) {
    unsigned int ret;
    if(minheap->size == 0)
        return -1;

    ret = minheap->array[0];

    minheap->array[0] = minheap->array[minheap->size - 1];
    minheap->size--;

    sift_down(0, minheap);
    return ret;
}

void build_min_heap_O_nlogn(min_heap_t * minheap, unsigned int * arr, unsigned int arr_size) {

    new_min_heap(minheap);

    for(unsigned int i = 0; i < arr_size; ++i)
        min_heap_add(arr[i], minheap);
}
