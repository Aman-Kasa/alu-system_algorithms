#include <stdlib.h>
#include "graphs.h"

/**
 * enqueue_edges - Enqueues all unvisited neighbors of a given vertex.
 * @v: The current vertex being processed.
 * @queue: The queue array storing vertices to visit.
 * @depths: The array tracking the depth of each vertex in the queue.
 * @tail: A pointer to the tail index of the queue.
 * @visited: The array tracking visited vertices.
 * @curr_depth: The depth of the current parent vertex.
 */
static void enqueue_edges(const vertex_t *v, const vertex_t **queue,
			  size_t *depths, size_t *tail,
			  int *visited, size_t curr_depth)
{
	edge_t *edge = v->edges;

	while (edge)
	{
		if (!visited[edge->dest->index])
		{
			visited[edge->dest->index] = 1;
			queue[*tail] = edge->dest;
			depths[*tail] = curr_depth + 1;
			(*tail)++;
		}
		edge = edge->next;
	}
}

/**
 * run_bfs - Processes the BFS queue loop.
 * @queue: The queue array storing vertices to visit.
 * @depths: The array tracking the depth of each vertex in the queue.
 * @visited: The array tracking visited vertices.
 * @action: A pointer to a function to be called for each visited vertex.
 * @tail: Current count of elements in the queue.
 *
 * Return: The biggest vertex depth reached.
 */
static size_t run_bfs(const vertex_t **queue, size_t *depths, int *visited,
		      void (*action)(const vertex_t *v, size_t depth),
		      size_t tail)
{
	size_t head = 0, max_depth = 0;
	const vertex_t *curr;
	size_t curr_depth;

	while (head < tail)
	{
		curr = queue[head];
		curr_depth = depths[head];
		action(curr, curr_depth);
		if (curr_depth > max_depth)
			max_depth = curr_depth;
		enqueue_edges(curr, queue, depths, &tail, visited, curr_depth);
		head++;
	}
	return (max_depth);
}

/**
 * breadth_first_traverse - Goes through a graph using breadth-first algorithm.
 * @graph: A pointer to the graph to traverse.
 * @action: A pointer to a function to be called for each visited vertex.
 *
 * Return: The biggest vertex depth, or 0 on failure.
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	const vertex_t **queue;
	size_t *depths, max_depth;
	int *visited;

	if (!graph || !action || !graph->vertices)
		return (0);

	queue = malloc(graph->nb_vertices * sizeof(*queue));
	depths = malloc(graph->nb_vertices * sizeof(*depths));
	visited = calloc(graph->nb_vertices, sizeof(*visited));

	if (!queue || !depths || !visited)
	{
		free(queue);
		free(depths);
		free(visited);
		return (0);
	}

	queue[0] = graph->vertices;
	depths[0] = 0;
	visited[graph->vertices->index] = 1;

	max_depth = run_bfs(queue, depths, visited, action, 1);

	free(queue);
	free(depths);
	free(visited);
	return (max_depth);
}
