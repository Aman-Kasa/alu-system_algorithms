#ifndef LOCAL_HUFFMAN_H
#define LOCAL_HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "../huffman.h"

int compress_file(const char *in, const char *out);
int decompress_file(const char *in, const char *out);
void free_tree(binary_tree_node_t *root);

#endif /* LOCAL_HUFFMAN_H */
