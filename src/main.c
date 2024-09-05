#include "../include/hash_table.h"

int main() {
    hash_table_t ht;

    new_hash_table(&ht);

    insert_hash_table(&ht, 'f');
    insert_hash_table(&ht, 'j');
    insert_hash_table(&ht, 't');
    insert_hash_table(&ht, 'd');
    insert_hash_table(&ht, 'v');
    insert_hash_table(&ht, 'n');

    free_hash_table(&ht);
}
