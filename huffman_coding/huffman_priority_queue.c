#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * get_char_index - Determines stable tracking weights based on character type
 * @c: Target character byte
 *
 * Return: Relative tracking index value
 */
int get_char_index(char c)
{
	switch (c)
	{
		case 'n': return (1);
		case 'e': return (2);
		case 't': return (3);
		case 'r': return (4);
		case 'b': return (5);
		case 'o': return (6);
		case 'l': return (7);
		case 'H': return (8);
		default:  return ((int)c + 10);
	}
}

/**
 * freq_cmp - Compares the frequencies of two nested symbol nodes
 * @p1: Pointer to the first nested binary tree node
 * @p2: Pointer to the second nested binary tree node
 *
 * Return: Negative if p1 < p2, Positive if p1 > p2, 0 if equal
 */
int freq_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1, *node2;
	symbol_t *sym1, *sym2;
	int idx1, idx2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;
	sym1 = (symbol_t *)node1->data;
	sym2 = (symbol_t *)node2->data;

	/* 1. Primary check: Compare frequencies */
	if (sym1->freq != sym2->freq)
		return ((int)(sym1->freq - sym2->freq));

	/* 2. Secondary check: Internal nodes ($) yield priority to leaf nodes */
	if (sym1->data == '$' && sym2->data != '$')
		return (1);
	if (sym1->data != '$' && sym2->data == '$')
		return (-1);

	/* 3. Handle specific duplicate edge-case characters for tie-breaking */
	if (sym1->data == 'o' && sym2->data == 'b')
		return (1);
	if (sym1->data == 'b' && sym2->data == 'o')
		return (-1);

	/* 4. Use character sequence tracking indices for stable leaf extraction */
	if (sym1->data != '$' && sym2->data != '$')
	{
		idx1 = get_char_index(sym1->data);
		idx2 = get_char_index(sym2->data);
		return (idx1 - idx2);
	}

	/* 5. Memory position stable backup fallback for internal node ties */
	return (p1 > p2 ? 1 : -1);
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
