#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include <stdbool.h>

typedef struct {
    unsigned int size;
    unsigned int capacity;
    unsigned int* array;
} min_heap_t;

bool new_min_heap(min_heap_t*);
void free_min_heap(min_heap_t*);
void min_heap_add(unsigned int, min_heap_t*);
unsigned int min_heap_extract(min_heap_t*);

#endif // _MIN_HEAP_H_
