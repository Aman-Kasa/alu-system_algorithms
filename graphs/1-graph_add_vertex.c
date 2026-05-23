#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph.
 * @graph: A pointer to the graph to add the vertex to.
 * @str: The string to store in the new vertex.
 *
 * Return: A pointer to the created vertex, or NULL on failure.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *curr;
	size_t idx = 0;

	if (!graph || !str)
		return (NULL);

	curr = graph->vertices;
	while (curr)
	{
		if (strcmp(curr->content, str) == 0)
			return (NULL);
		if (curr->next == NULL)
		{
			idx = curr->index + 1;
			break;
		}
		curr = curr->next;
	}

	new_vertex = malloc(sizeof(*new_vertex));
	if (!new_vertex)
		return (NULL);

	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index = (graph->vertices == NULL) ? 0 : idx;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!graph->vertices)
		graph->vertices = new_vertex;
	else
		curr->next = new_vertex;

	graph->nb_vertices++;
	return (new_vertex);
}
