#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

/**
 * graph_backtrack - Recursive helper function that uses depth-first search
 * to find a path from a current vertex to a target vertex.
 * @curr: Pointer to the current vertex being evaluated.
 * @target: Pointer to the destination vertex.
 * @visited: Array of strings tracking names of already visited vertices.
 * @visited_count: Pointer to the number of vertices in the visited array.
 * @path: Queue storing the final successful path sequence.
 *
 * Return: 1 if the target vertex is reached, 0 otherwise.
 */
int graph_backtrack(vertex_t const *curr, vertex_t const *target,
		    char **visited, int *visited_count, queue_t *path)
{
	edge_t *edge;
	int i;

	if (!curr || !target)
		return (0);

	for (i = 0; i < *visited_count; i++)
	{
		if (strcmp(visited[i], curr->content) == 0)
			return (0);
	}

	printf("Checking %s\n", curr->content);

	visited[*visited_count] = curr->content;
	(*visited_count)++;

	if (strcmp(curr->content, target->content) == 0)
	{
		queue_push_front(path, strdup(curr->content));
		return (1);
	}

	for (edge = curr->edges; edge != NULL; edge = edge->next)
	{
		if (!edge->dest)
			continue;

		if (graph_backtrack(edge->dest, target, visited, visited_count, path))
		{
			queue_push_front(path, strdup(curr->content));
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
	char **visited;
	int visited_count = 0;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = malloc(graph->nb_vertices * sizeof(char *));
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (!graph_backtrack(start, target, visited, &visited_count, path))
	{
		free(visited);
		free(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
