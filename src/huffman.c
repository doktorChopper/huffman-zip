#include "../include/huffman.h"
#include "../include/min_heap.h"
#include <stdio.h>

static void build_min_heap_from_hash_table(min_heap_t*, hash_table_t*);

static void build_min_heap_from_hash_table(min_heap_t* minheap, hash_table_t* table) {
    new_min_heap(minheap); 

    for(unsigned int i = 0; i < table->capacity; ++i) {
        if(table->table[i])
            min_heap_add(new_min_heap_node(table->table[i]->key, table->table[i]->count), minheap);
    }
}

unsigned int symbols_frequency(FILE *f, hash_table_t* freq) {
    char c;
    unsigned int symbols_count = 0;

    while((c = fgetc(f)) != EOF) {
        insert_hash_table(c, freq);
        symbols_count++;
    }

    return symbols_count;
}



void build_huffman_tree(min_heap_t * huffman_tree, hash_table_t * freq) {

    

}



void build_huffman_codetable(FILE *in) {

    unsigned int symbols_count;
    hash_table_t freq;
    min_heap_t huffman_tree;

    new_hash_table(&freq);
    
    symbols_count = symbols_frequency(in, &freq);

    new_min_heap(&huffman_tree);
    build_huffman_tree(&huffman_tree, &freq);


    free_min_heap(&huffman_tree);
    free_hash_table(&freq);
}
