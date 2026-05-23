#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * connect_edge - Connects a destination vertex to a source edge map list.
 * @src_v: Source vertex.
 * @dest_v: Target vertex.
 *
 * Return: 1 on success, 0 on failure.
 */
static int connect_edge(vertex_t *src_v, vertex_t *dest_v)
{
	edge_t *edge, *curr;

	edge = malloc(sizeof(*edge));
	if (!edge)
		return (0);
	edge->dest = dest_v;
	edge->next = NULL;

	if (!src_v->edges)
	{
		src_v->edges = edge;
	}
	else
	{
		curr = src_v->edges;
		while (curr->next)
		{
			if (curr->dest == dest_v)
			{
				free(edge);
				return (1);
			}
			curr = curr->next;
		}
		if (curr->dest == dest_v)
		{
			free(edge);
			return (1);
		}
		curr->next = edge;
	}
	src_v->nb_edges++;
	return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices to an existing graph.
 * @graph: A pointer to the graph to add the edge to.
 * @src: The string identifying the source vertex.
 * @dest: The string identifying the destination vertex.
 * @type: The type of edge (UNIDIRECTIONAL or BIDIRECTIONAL).
 *
 * Return: 1 on success, 0 on failure.
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   edge_type_t type)
{
	vertex_t *curr, *src_v = NULL, *dest_v = NULL;

	if (!graph || !src || !dest)
		return (0);

	curr = graph->vertices;
	while (curr)
	{
		if (strcmp(curr->content, src) == 0)
			src_v = curr;
		if (strcmp(curr->content, dest) == 0)
			dest_v = curr;
		curr = curr->next;
	}

	if (!src_v || !dest_v)
		return (0);

	if (!connect_edge(src_v, dest_v))
		return (0);

	if (type == BIDIRECTIONAL)
	{
		if (!connect_edge(dest_v, src_v))
			return (0);
	}

	return (1);
}
