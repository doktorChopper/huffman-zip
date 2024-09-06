#include "../include/huffman.h"
#include <stdio.h>
    

unsigned int symbols_frequency(FILE *f, hash_table_t* freq) {
    char c;
    unsigned int symbols_count = 0;

    while((c = fgetc(f)) != EOF) {
        insert_hash_table(freq, c); 
        symbols_count++;
    }

    return symbols_count;
}

