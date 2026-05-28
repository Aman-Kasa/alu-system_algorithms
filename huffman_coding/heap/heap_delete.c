#include <stdlib.h>
#include "heap.h"

/**
 * free_tree - Recursively deletes nodes of a binary tree
 * @node: Current node
 * @free_data: Pointer to data clearing function
 */
void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	free_tree(node->left, free_data);
	free_tree(node->right, free_data);

	if (free_data && node->data)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deallocates a heap structure completely
 * @heap: Pointer to the heap
 * @free_data: Pointer to function used to free content of nodes
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	free_tree(heap->root, free_data);
	free(heap);
}
