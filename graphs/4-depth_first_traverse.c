#include <stdlib.h>
#include "graphs.h"

/**
 * dfs_explore - Explores a graph starting from a node using recursion.
 * @v: Current vertex node.
 * @visited: Array tracking visited states.
 * @depth: Current depth index.
 * @action: The function pointer to invoke upon discovering a node.
 *
 * Return: Max tracked path depth configuration reached.
 */
static size_t dfs_explore(const vertex_t *v, int *visited, size_t depth,
			  void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *edge;
	size_t current_max = depth, branch_depth;

	if (!v || visited[v->index])
		return (0);

	visited[v->index] = 1;
	action(v, depth);

	edge = v->edges;
	while (edge)
	{
		if (!visited[edge->dest->index])
		{
			branch_depth = dfs_explore(edge->dest, visited,
						   depth + 1, action);
			if (branch_depth > current_max)
				current_max = branch_depth;
		}
		edge = edge->next;
	}

	return (current_max);
}

/**
 * depth_first_traverse - Explores graph using DFS algorithm mechanics.
 * @graph: Graph structure pointer.
 * @action: Function pointer wrapper to execute.
 *
 * Return: Deepest recursive branch length reached.
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_depth = 0;

	if (!graph || !action || !graph->vertices)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (0);

	max_depth = dfs_explore(graph->vertices, visited, 0, action);
	free(visited);

	return (max_depth);
}
