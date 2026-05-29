#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds a Huffman tree from data and frequencies
 * @data: Array of characters
 * @freq: Array containing the associated frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the root node of the Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *pq = NULL;
	binary_tree_node_t *root = NULL;

	if (!data || !freq || size == 0)
		return (NULL);

	pq = huffman_priority_queue(data, freq, size);
	if (!pq)
		return (NULL);

	while (pq->root && (pq->root->left || pq->root->right))
	{
		if (!huffman_extract_and_insert(pq))
		{
			heap_delete(pq, NULL);
			return (NULL);
		}
	}

	if (pq->root)
	{
		root = (binary_tree_node_t *)pq->root->data;
	}

	heap_delete(pq, NULL);

	return (root);
}
