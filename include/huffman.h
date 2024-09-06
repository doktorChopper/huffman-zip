#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>

#include "../include/hash_table.h"

void huffman_encode();
void huffman_decode();

unsigned int symbols_frequency(FILE*, hash_table_t*);
#endif // _HUFFAN_H_
