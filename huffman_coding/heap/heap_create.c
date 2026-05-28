#include <stdlib.h>
#include "heap.h"

/**
 * heap_create - Creates a Heap data structure
 * @data_cmp: Pointer to the function used to compare two nodes' data
 *
 * Return: Pointer to the created heap_t structure, or NULL if it fails
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	heap = malloc(sizeof(heap_t));
	if (heap == NULL)
	{
		return (NULL);
	}

	heap->size = 0;
	heap->root = NULL;
	heap->data_cmp = data_cmp;

	return (heap);
}
