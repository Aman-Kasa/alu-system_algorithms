#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds a Huffman tree from characters and their frequencies
 * @data: Array of characters
 * @freq: Array of frequencies (same size as data)
 * @size: Number of elements in data and freq
 *
 * Return: Pointer to root of Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *q;
	binary_tree_node_t *root;

	if (!data || !freq || size == 0)
		return (NULL);

	q = huffman_priority_queue(data, freq, size);
	if (!q)
		return (NULL);

	while (q->size > 1)
	{
		if (!huffman_extract_and_insert(q))
		{
			heap_delete(q, NULL);
			return (NULL);
		}
	}

	if (q->root)
		root = (binary_tree_node_t *)q->root->data;
	else
		root = NULL;

	heap_delete(q, NULL);

	return (root);
}
