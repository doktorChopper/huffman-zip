#include "../include/iss1_huffman.h"
#include "../include/iss1.h"
#include <stdio.h>

unsigned int symbols_frequency(FILE * in, iss1_hash_table_t* table) {
    char c;
    unsigned int symbols_count;

    while((c = fgetc(in)) != EOF) {
        insert_iss1_hash_table(c, table);
        symbols_count++;
    }

    return symbols_count;
}


void build_huffman_code_table(FILE* in) {
    iss1_hash_table_t freq_table;
    iss1_min_heap_t min_heap;

    new_iss1_hash_table(&freq_table);
    symbols_frequency(in, &freq_table);

    build_iss1_min_heap_from_array_O_nlong(&min_heap, freq_table.table, freq_table.size);

    free_iss1_min_heap(&min_heap);
    free_iss1_hash_table(&freq_table);
}
