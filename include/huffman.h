#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>

#include "../include/hash_table.h"
#include "../include/min_heap.h"

void huffman_encode();
void huffman_decode();

unsigned int symbols_frequency(FILE*, hash_table_t*);
void build_huffman_codetable(FILE*);
void code_calculate(min_heap_t*);
void build_huffman_tree(min_heap_t*, hash_table_t*);

#endif // _HUFFAN_H_
