#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

/**
 * graph_backtrack - Recursive helper function that uses depth-first search
 * to find a path from a current vertex to a target vertex.
 * @curr: Pointer to the current vertex being evaluated.
 * @target: Pointer to the destination vertex.
 * @visited: Array tracking visited statuses by vertex index.
 * @path: Queue storing the final successful path sequence strings.
 *
 * Return: 1 if the target vertex is reached, 0 otherwise.
 */
int graph_backtrack(vertex_t const *curr, vertex_t const *target,
		    char *visited, queue_t *path)
{
	edge_t *edge;

	if (!curr || !target || visited[curr->index])
		return (0);

	printf("Checking %s\n", curr->content);
	visited[curr->index] = 1;

	if (strcmp(curr->content, target->content) == 0)
	{
		queue_enqueue(path, strdup(curr->content));
		return (1);
	}

	for (edge = curr->edges; edge != NULL; edge = edge->next)
	{
		if (graph_backtrack(edge->dest, target, visited, path))
		{
			queue_enqueue(path, strdup(curr->content));
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_graph - Searches for the first path from a starting vertex
 * to a target vertex in a graph using recursive backtracking.
 * @graph: Pointer to the graph structure.
 * @start: Pointer to the starting vertex.
 * @target: Pointer to the target vertex.
 *
 * Return: Pointer to a queue containing the path, or NULL on failure.
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	queue_t *path;
	char *visited;
	size_t num_vertices;

	if (!graph || !start || !target)
		return (NULL);

	num_vertices = graph->nb_vertices > 0 ? graph->nb_vertices : 1024;

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(num_vertices, sizeof(char));
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (!graph_backtrack(start, target, visited, path))
	{
		free(visited);
		free(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
