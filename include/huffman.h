#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>

#include "../include/hash_table.h"
#include "../include/min_heap.h"
#include "../include/bitset.h"

void huffman_encode();
void huffman_decode();

unsigned int symbols_frequency(FILE*, hash_table_t*);
void build_huffman_tree(min_heap_t*, hash_table_t*);
void build_huffman_codetable(FILE *);


//TODO

void read_codetable();
void write_code_table();

#endif // _HUFFAN_H_
