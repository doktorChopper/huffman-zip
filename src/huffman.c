#include "../include/huffman.h"
#include "../include/min_heap.h"
#include <stdio.h>

static void min_heap_from_hash_table(min_heap_t*, hash_table_t*);
    

static void min_heap_from_hash_table(min_heap_t* huffman_tree, hash_table_t* freq) {

    for( unsigned int i = 0; i < freq->size; ++i) {
        if(freq->table[i] == NULL) continue;
        min_heap_add(freq->table[i]->key, huffman_tree); 
    }
}

unsigned int symbols_frequency(FILE *f, hash_table_t* freq) {
    char c;
    unsigned int symbols_count = 0;

    while((c = fgetc(f)) != EOF) {
        insert_hash_table(freq, c); 
        symbols_count++;
    }

    return symbols_count;
}



void build_huffman_tree(min_heap_t * huffman_tree, hash_table_t * freq) {

    min_heap_from_hash_table(huffman_tree, freq);
    
}



void build_huffman_codetable(FILE *in) {

    unsigned int symbols_count;
    hash_table_t freq;
    min_heap_t huffman_tree;

    new_hash_table(&freq);
    
    symbols_count = symbols_frequency(in, &freq);

    free_hash_table(&freq);
}
