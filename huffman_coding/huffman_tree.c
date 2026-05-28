#include <stdlib.h>
#include "huffman.h"

/**
 * huffman_tree - Builds the complete Huffman tree structure
 * @data: Array of characters
 * @freq: Array of character frequencies
 * @size: Size of input arrays
 *
 * Return: Pointer to the root node of the Huffman tree, or NULL if it fails
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *root, *nested_root;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	nested_root = (binary_tree_node_t *)heap_extract(priority_queue);
	root = nested_root;

	heap_delete(priority_queue, NULL);
	return (root);
}
