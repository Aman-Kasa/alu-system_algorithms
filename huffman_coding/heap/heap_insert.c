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
 * find_parent - Finds the parent node for the next insertion slot
 * @root: Root of the heap tree
 * @size: Current size of the heap before insertion
 *
 * Return: Pointer to the parent node
 */
binary_tree_node_t *find_parent(binary_tree_node_t *root, size_t size)
{
	size_t mask;

	mask = 1;
	while (mask <= size)
		mask <<= 1;
	mask >>= 2;

	while (mask > 1)
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
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap in which the node has to be inserted
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;

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

	parent = find_parent(heap->root, heap->size + 1);
	new_node->parent = parent;

	if (!(heap->size & 1))
		parent->right = new_node;
	else
		parent->left = new_node;

	heap->size++;
	bubble_up(heap, new_node);

	return (new_node);
}
