#include <stdlib.h>
#include "heap.h"

/**
 * bubble_up - Restores min-heap property by floating up a node
 * @heap: Pointer to the heap
 * @node: Pointer to the newly inserted node
 */
void bubble_up(heap_t *heap, binary_tree_node_t *node)
{
	void *temp;

	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap in which the node has to be inserted
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;
	size_t mask, target_idx;

	if (!heap || !data)
		return (NULL);

	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);

	if (!heap->root)
	{
		heap->root = new_node;
		heap->size++;
		return (new_node);
	}

	/* target_idx represents the 1-based index of the new node */
	target_idx = heap->size + 1;
	parent = heap->root;

	/* Find the highest bit in target_idx (e.g., for 6 [110], mask becomes 4 [100]) */
	mask = 1;
	while (mask <= target_idx)
		mask <<= 1;
	mask >>= 2; /* Shift past the highest bit since root is already found */

	/* Move down the tree until we are exactly at the parent node */
	while (mask > 1)
	{
		if (target_idx & mask)
			parent = parent->right;
		else
			parent = parent->left;
		mask >>= 1;
	}

	/* Connect the parent to the new node based on the last bit */
	new_node->parent = parent;
	if (target_idx & 1)
		parent->right = new_node;
	else
		parent->left = new_node;

	heap->size++;
	bubble_up(heap, new_node);

	return (new_node);
}
