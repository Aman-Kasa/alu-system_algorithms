#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * find_last_vertex - Finds the tail of the vertex list and checks duplicates.
 * @head: Pointer to the head vertex node.
 * @str: The content string to search for duplicates.
 *
 * Return: Pointer to the last vertex, or NULL if a duplicate is found.
 */
static vertex_t *find_last_vertex(vertex_t *head, const char *str)
{
	vertex_t *curr = head;

	while (curr)
	{
		if (strcmp(curr->content, str) == 0)
			return (NULL);
		if (!curr->next)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * graph_add_vertex - Adds a vertex to an existing graph.
 * @graph: A pointer to the graph to add the vertex to.
 * @str: The string to store in the new vertex.
 *
 * Return: A pointer to the created vertex, or NULL on failure.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *tail = NULL;

	if (!graph || !str)
		return (NULL);

	if (graph->vertices)
	{
		tail = find_last_vertex(graph->vertices, str);
		if (!tail)
			return (NULL);
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

	new_vertex->index = graph->nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!graph->vertices)
		graph->vertices = new_vertex;
	else
		tail->next = new_vertex;

	graph->nb_vertices++;
	return (new_vertex);
}
