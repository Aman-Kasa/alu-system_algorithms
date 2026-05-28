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

	/* Create priority queue from data and frequencies */
	pq = huffman_priority_queue(data, freq, size);
	if (!pq)
		return (NULL);

	/* Combine nodes until only 1 root node remains in the queue */
	while (pq->root && (pq->root->left || pq->root->right))
	{
		if (!huffman_extract_and_insert(pq))
		{
			heap_delete(pq, NULL);
			return (NULL);
		}
	}

	/* Extract the Huffman tree root nested inside the last node */
	if (pq->root)
	{
		root = (binary_tree_node_t *)pq->root->data;
	}

	/* Free the priority queue structure shell itself */
	free(pq);

	return (root);
}
