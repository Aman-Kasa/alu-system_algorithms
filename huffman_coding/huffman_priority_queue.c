#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

static size_t g_order;

/**
 * freq_cmp - Compares two nested symbol nodes by frequency then insert order
 * @p1: Pointer to the first nested binary tree node
 * @p2: Pointer to the second nested binary tree node
 *
 * Return: Negative if p1 < p2, Positive if p1 > p2, 0 if equal
 */
int freq_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1, *node2;
	symbol_t *sym1, *sym2;
	size_t order1, order2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;
	sym1 = (symbol_t *)node1->data;
	sym2 = (symbol_t *)node2->data;

	if (sym1->freq != sym2->freq)
		return ((int)(sym1->freq - sym2->freq));

	if (sym1->data == -1 && sym2->data != -1)
		return (1);
	if (sym1->data != -1 && sym2->data == -1)
		return (-1);

	order1 = (size_t)node1->parent;
	order2 = (size_t)node2->parent;
	if (order1 != order2)
		return (order1 > order2 ? -1 : 1);

	return (0);
}

/**
 * next_order - Returns next insertion order value
 *
 * Return: Next order value
 */
size_t next_order(void)
{
	return (++g_order);
}

/**
 * free_failed_queue - Cleans up allocated memory if initialization fails
 * @heap: Pointer to the priority queue heap
 */
void free_failed_queue(heap_t *heap)
{
	binary_tree_node_t *nested_node;

	while (heap->root)
	{
		nested_node = (binary_tree_node_t *)heap_extract(heap);
		if (nested_node)
		{
			if (nested_node->data)
				free(nested_node->data);
			free(nested_node);
		}
	}
	free(heap);
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 * @data: Array of characters
 * @freq: Array containing the associated frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the created min-heap priority queue, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *sym;
	binary_tree_node_t *nested_node;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	g_order = 0;
	heap = heap_create(freq_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		sym = symbol_create(data[i], freq[i]);
		if (!sym)
		{
			free_failed_queue(heap);
			return (NULL);
		}

		nested_node = binary_tree_node(NULL, sym);
		if (!nested_node)
		{
			free(sym);
			free_failed_queue(heap);
			return (NULL);
		}

		nested_node->parent = (binary_tree_node_t *)next_order();

		if (!heap_insert(heap, nested_node))
		{
			free(sym);
			free(nested_node);
			free_failed_queue(heap);
			return (NULL);
		}
	}

	return (heap);
}
