#include "../include/iss1_huffman.h"
#include <stdio.h>

int main() {

    FILE* fp = fopen("./test.txt", "r");
    build_huffman_code_table(fp);

    fclose(fp);
}
