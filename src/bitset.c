#include "../include/bitset.h"

#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 16

static const unsigned int default_bitset_capacity = DEFAULT_CAPACITY;

bitset_t* new_bitset() {
    bitset_t* bs = (bitset_t*) malloc(sizeof(bitset_t));

    bs->bits = (uint64_t*) malloc(default_bitset_capacity * sizeof(uint64_t));
    bs->capacity = default_bitset_capacity;
    bs->size = 0;

    return bs;
}


void free_bitset(bitset_t * bitset) {
    free(bitset->bits);
    free(bitset);
}

void bitset_reset(bitset_t * bitset, unsigned int index) {
    bitset->bits[_byte_index(index)] &= ~(_bitset_index(index));
}

void bitset_set(bitset_t * bitset, unsigned int index) {
    bitset->bits[_byte_index(index)] |= _bitset_index(index);
}

unsigned int _byte_index(unsigned int index) {
    return index / 8;
}

uint8_t _bitset_index(unsigned int index) {
    return 1 << _bitset_offset(index);
}

uint8_t _bitset_offset(unsigned int index) {
    return 7 - (index % 8);
}
