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

	/* Create priority queue (min heap) */
	q = huffman_priority_queue(data, freq, size);
	if (!q)
		return (NULL);

	/* Repeatedly extract two smallest nodes and merge until one node remains */
	while (q->root && (q->root->left || q->root->right))
	{
		if (!huffman_extract_and_insert(q))
		{
			heap_delete(q, NULL);
			return (NULL);
		}
	}

	/* The remaining node inside the priority queue heap holds our root */
	if (q->root)
		root = (binary_tree_node_t *)q->root->data;
	else
		root = NULL;

	/* Safe structural cleanup without destroying the target tree memory */
	heap_delete(q, NULL);

	return (root);
}
