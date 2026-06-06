#include "pathfinding.h"

/**
 * graph_dfs - Recursive helper to traverse the graph using depth-first search
 * @curr: Current vertex being inspected
 * @target: Ultimate destination target vertex
 * @visited: Array tracking visited vertices by their indices
 * @path: Queue tracking the successful path sequence
 *
 * Return: 1 if path to target found, 0 otherwise
 */
int graph_dfs(vertex_t const *curr, vertex_t const *target,
	      char *visited, queue_t *path)
{
	edge_t *edge;
	char *city_copy;

	if (!curr || visited[curr->index])
		return (0);

	printf("Checking %s\n", curr->content);
	visited[curr->index] = 1;

	if (strcmp(curr->content, target->content) == 0)
	{
		city_copy = strdup(curr->content);
		if (!city_copy)
			return (0);
		queue_push_front(path, city_copy);
		return (1);
	}

	for (edge = curr->edges; edge; edge = edge->next)
	{
		if (graph_dfs(edge->dest, target, visited, path))
		{
			city_copy = strdup(curr->content);
			if (!city_copy)
				return (0);
			queue_push_front(path, city_copy);
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_graph - Searches for the first valid path in a graph
 * @graph: Pointer to the structural graph wrapper
 * @start: Starting vertex node pointer
 * @target: Ending target vertex node pointer
 *
 * Return: Allocates and returns a queue path sequence, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	queue_t *path;
	char *visited;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (!graph_dfs(start, target, visited, path))
	{
		free(visited);
		queue_delete(path);
		return (NULL);
	}

	free(visited);
	return (path);
}
