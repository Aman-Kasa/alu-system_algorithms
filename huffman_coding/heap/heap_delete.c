#include <stdlib.h>
#include "heap.h"

/**
 * free_binary_tree - Recursively frees nodes using post-order traversal
 * @node: Pointer to the current node being freed
 * @free_data: Pointer to the function used to free data, or NULL
 */
void free_binary_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	free_binary_tree(node->left, free_data);
	free_binary_tree(node->right, free_data);

	if (free_data && node->data)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deallocates an entire Min Binary Heap structure
 * @heap: Pointer to the heap structure to delete
 * @free_data: Pointer to a function used to free node data contents
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	free_binary_tree(heap->root, free_data);
	free(heap);
}
