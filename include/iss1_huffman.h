#ifndef _ISS1_HUFFMAN_H_
#define _ISS1_HUFFMAN_H_

#include <stdio.h>

#include "../include/iss1.h"

unsigned int symbols_frequency(FILE*, iss1_hash_table_t*);

void build_huffman_code_table(FILE*);

#endif // _ISS1_HUFFMAN_H_
