#include "../include/huffman.h"
#include "../include/min_heap.h"
#include <stdio.h>
#include <stdlib.h>

static void build_min_heap_from_hash_table(min_heap_t*, hash_table_t*);
static void free_huffman_tree(min_heap_t*);
static void free_huffman_tree_helper(min_heap_node_t*);

static void build_min_heap_from_hash_table(min_heap_t* minheap, hash_table_t* table) {

    for(unsigned int i = 0; i < table->capacity; ++i) {
        if(table->table[i])
            min_heap_add(new_min_heap_node(table->table[i]->key, table->table[i]->count), minheap);
    }
}

static void free_huffman_tree_helper(min_heap_node_t* root) {
    if(!root)
        return;
    free_huffman_tree_helper(root->left);
    free_huffman_tree_helper(root->right);
    free(root);
    root = NULL;
}

static void free_huffman_tree(min_heap_t* huffman_tree) {
    free_huffman_tree_helper(huffman_tree->array[0]);
    free(huffman_tree->array);
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


void code_calculate(min_heap_t * minheap) {

}


void build_huffman_tree(min_heap_t * huffman_tree, hash_table_t * freq) {

    build_min_heap_from_hash_table(huffman_tree, freq);

    min_heap_node_t* ext_right;
    min_heap_node_t* ext_left;
    min_heap_node_t* parent;

    while (huffman_tree->size != 1) {
        ext_right = min_heap_extract(huffman_tree);    
        ext_left = min_heap_extract(huffman_tree);    

        parent = new_min_heap_node('$', ext_right->freq + ext_left->freq);
        parent->left = ext_left;
        parent->right = ext_right;

        min_heap_add(parent, huffman_tree);
    }
}



void build_huffman_codetable(FILE *in) {

    unsigned int symbols_count;
    hash_table_t freq;
    min_heap_t huffman_tree;

    new_hash_table(&freq);
    
    symbols_count = symbols_frequency(in, &freq);

    new_min_heap(&huffman_tree);
    build_huffman_tree(&huffman_tree, &freq);

    free_huffman_tree(&huffman_tree);
    //free_min_heap(&huffman_tree);
    free_hash_table(&freq);
}
