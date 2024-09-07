#include "../include/huffman.h"
#include "../include/min_heap.h"
#include "../include/bitset.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    unsigned int code_len;
    bitset_t* code;
} huffman_code_t;

static void build_min_heap_from_hash_table(min_heap_t*, hash_table_t*);
static void free_huffman_tree(min_heap_t*);
static void free_huffman_tree_helper(min_heap_node_t*);
static void code_calculate(min_heap_node_t*, huffman_code_t*);

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


static huffman_code_t new_code(min_heap_node_t* leaf) {

    unsigned int depth = 0;
    unsigned int i = 0;
    huffman_code_t ret;

    bitset_t *code = new_bitset();
    
    while(leaf && leaf->parent) {
        if(leaf == leaf->parent->right) 
            bitset_set(code, i); 
        
        leaf = leaf->parent;
        ++depth; 
        ++i;
    }

    ret.code_len = depth;
    ret.code = code;
    return ret;
}

static void code_calculate(min_heap_node_t* root, huffman_code_t* code_table) {
    if(!root) 
        return;

    if(root->left == NULL && root->right == NULL)
        code_table[root->key % 256] = new_code(root);
    else {
        code_calculate(root->left, code_table);
        code_calculate(root->right, code_table);
    }
      
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
        parent->left->parent = parent;
        parent->right->parent = parent;

        min_heap_add(parent, huffman_tree);
    }
}

static void free_code_table(huffman_code_t* code_table, unsigned int size) {
    for(unsigned int i = 0; i < size; ++i)
        if(code_table[i].code != NULL)
            free_bitset(code_table[i].code);
}

void build_huffman_codetable(FILE *in) {

    unsigned int symbols_count;
    hash_table_t freq;
    min_heap_t huffman_tree;
    huffman_code_t code_table[256];

    for(unsigned int i = 0; i < 256; ++i) {
        code_table[i].code = NULL;
        code_table[i].code_len = 0;
    }

    new_hash_table(&freq);
    
    symbols_count = symbols_frequency(in, &freq);

    new_min_heap(&huffman_tree);
    build_huffman_tree(&huffman_tree, &freq);

    code_calculate(huffman_tree.array[0], code_table);

    free_code_table(code_table, 256);

    free_huffman_tree(&huffman_tree);
    //free_min_heap(&huffman_tree);
    free_hash_table(&freq);
}
