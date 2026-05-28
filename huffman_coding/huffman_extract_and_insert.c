#include <stdlib.h>
#include "huffman.h"
#include "heap/heap.h"

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a new parent node
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left_nested, *right_nested, *parent_nested;
	symbol_t *sum_sym;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	left_nested = (binary_tree_node_t *)heap_extract(priority_queue);
	right_nested = (binary_tree_node_t *)heap_extract(priority_queue);

	if (!left_nested || !right_nested)
		return (0);

	sum_sym = symbol_create('$', ((symbol_t *)left_nested->data)->freq +
			     ((symbol_t *)right_nested->data)->freq);
	if (!sum_sym)
		return (0);

	parent_nested = binary_tree_node(NULL, sum_sym);
	if (!parent_nested)
	{
		free(sum_sym);
		return (0);
	}

	parent_nested->left = left_nested;
	parent_nested->right = right_nested;
	left_nested->parent = parent_nested;
	right_nested->parent = parent_nested;

	if (!heap_insert(priority_queue, parent_nested))
		return (0);

	return (1);
}
