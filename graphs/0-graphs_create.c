#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - Allocates memory to store a graph_t structure,
 *                and initializes its content.
 *
 * Return: A pointer to the allocated structure, or NULL on failure.
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(*graph));
	if (!graph)
		return (NULL);

	graph->nb_vertices = 0;
	graph->vertices = NULL;

	return (graph);
}
