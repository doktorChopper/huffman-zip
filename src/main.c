#include "../include/huffman.h"
#include <stdio.h>

int main() {

    FILE* fp = fopen("./test.txt", "r");
    build_huffman_codetable(fp);

    fclose(fp);
}
