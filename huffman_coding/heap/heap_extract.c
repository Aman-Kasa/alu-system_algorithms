#include <stdlib.h>
#include "heap.h"

/**
 * bubble_down - Restores min-heap property from the root down to leaves
 * @heap: Pointer to the heap
 * @node: Pointer to the node to bubble down
 */
void bubble_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest;
	void *temp;

	while (node->left)
	{
		smallest = node->left;
		if (node->right && heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (heap->data_cmp(node->data, smallest->data) <= 0)
			break;

		temp = node->data;
		node->data = smallest->data;
		smallest->data = temp;
		node = smallest;
	}
}

/**
 * get_last_node - Locates the last node in a complete binary tree
 * @root: Pointer to the root of the tree
 * @size: Total number of nodes in the heap
 *
 * Return: Pointer to the last node
 */
binary_tree_node_t *get_last_node(binary_tree_node_t *root, size_t size)
{
	size_t mask;

	mask = 1;
	while (mask <= size)
		mask <<= 1;
	mask >>= 2;

	while (mask > 0)
	{
		if (size & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
	}
	return (root);
}

/**
 * heap_extract - Extracts the root value from a Min Binary Heap
 * @heap: Pointer to the heap from which to extract the value
 *
 * Return: Pointer to the data stored in the root node, or NULL if it fails
 */
void *heap_extract(heap_t *heap)
{
	void *extracted_data;
	binary_tree_node_t *last_node, *parent;

	if (!heap || !heap->root)
		return (NULL);

	extracted_data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size--;
		return (extracted_data);
	}

	last_node = get_last_node(heap->root, heap->size);
	heap->root->data = last_node->data;

	parent = last_node->parent;
	if (parent->left == last_node)
		parent->left = NULL;
	else
		parent->right = NULL;

	free(last_node);
	heap->size--;

	bubble_down(heap, heap->root);

	return (extracted_data);
}
