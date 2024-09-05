#ifndef _BITSET_H_
#define _BITSET_H_

#include <stdint.h>

typedef struct {
    uint8_t* bits;
    unsigned int size;
    unsigned int capacity;
} bitset_t;

bitset_t* new_bitset();
void free_bitset(bitset_t*);

void bitset_set(bitset_t*, unsigned int);
void bitset_reset(bitset_t*, unsigned int);

uint8_t _bitset_index(unsigned int);
uint8_t _bitset_offset(unsigned int);
unsigned int _byte_index(unsigned int);

#endif // _BITSET_H_
