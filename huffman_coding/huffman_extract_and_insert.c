#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a parent node
 * @p_queue: Pointer to the priority queue min-heap
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *p_queue)
{
	binary_tree_node_t *first, *second, *parent;
	symbol_t *sym1, *sym2, *parent_sym;

	if (!p_queue || !p_queue->root)
		return (0);

	first = (binary_tree_node_t *)heap_extract(p_queue);
	second = (binary_tree_node_t *)heap_extract(p_queue);
	if (!first || !second)
	{
		if (first)
			free(first->data), free(first);
		return (0);
	}

	sym1 = (symbol_t *)first->data;
	sym2 = (symbol_t *)second->data;
	parent_sym = symbol_create(-1, sym1->freq + sym2->freq);
	if (!parent_sym)
		return (0);

	parent = binary_tree_node(NULL, parent_sym);
	if (!parent)
	{
		free(parent_sym);
		return (0);
	}

	parent->left = first;
	parent->right = second;
	first->parent = parent;
	second->parent = parent;

	if (!heap_insert(p_queue, parent))
	{
		free(parent_sym), free(parent);
		return (0);
	}

	return (1);
}
