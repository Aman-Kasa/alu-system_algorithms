#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds a complete Huffman tree pipeline
 * @data: Array of characters of size size
 * @freq: Array containing the associated frequencies of size size
 * @size: Size of the arrays
 *
 * Return: Pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *huffman_root;

	if (!data || !freq || size == 0)
		return (NULL);

	/* Step 1: Initialize the priority queue */
	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	/* Step 2: Combine nodes until only one remains */
	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	/* Step 3: Extract the final remaining node (the Huffman tree root) */
	huffman_root = (binary_tree_node_t *)heap_extract(priority_queue);
	if (!huffman_root)
	{
		heap_delete(priority_queue, NULL);
		return (NULL);
	}

	/* Step 4: Deallocate the priority queue tracking framework itself */
	heap_delete(priority_queue, NULL);

	return (huffman_root);
}
