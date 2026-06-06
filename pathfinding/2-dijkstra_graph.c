#include "pathfinding.h"

/**
 * find_min_vertex - Finds the unvisited vertex with the minimum distance
 * @vertices: Head pointer to the list of vertices
 * @dist: Array of distances
 * @visited: Array tracking visited status
 *
 * Return: Pointer to the vertex with minimum distance, or NULL
 */
static vertex_t *find_min_vertex(vertex_t *vertices, int *dist, char *visited)
{
	vertex_t *min_v = NULL;
	vertex_t *curr;
	int min_dist = INT_MAX;

	for (curr = vertices; curr; curr = curr->next)
	{
		if (!visited[curr->index] && dist[curr->index] < min_dist)
		{
			min_dist = dist[curr->index];
			min_v = curr;
		}
	}
	return (min_v);
}

/**
 * build_dijkstra_path - Unwinds parent paths back into a sequence path queue
 * @target: Target destination vertex
 * @parent: Array of parent vertex pointers
 * @path: Resulting path tracker queue
 *
 * Return: 1 on success, 0 on memory allocation failure
 */
static int build_dijkstra_path(vertex_t const *target, vertex_t **parent,
			       queue_t *path)
{
	vertex_t const *curr = target;
	char *city_copy;

	while (curr)
	{
		city_copy = strdup(curr->content);
		if (!city_copy)
			return (0);
		queue_push_front(path, city_copy);
		curr = parent[curr->index];
	}
	return (1);
}

/**
 * run_dijkstra - Core execution loop for Dijkstra algorithm updates
 * @graph: Graph structure pointer wrapper
 * @dist: Dynamic distances mapping storage allocation
 * @visited: Visited indices array tracking matrix map
 * @parent: Parent history tracing sequence configuration
 * @target: Objective goal target node
 */
static void run_dijkstra(graph_t *graph, int *dist, char *visited,
			 vertex_t **parent, vertex_t const *target)
{
	vertex_t *curr;
	edge_t *edge;
	int new_dist;
	char const *p_name;

	while ((curr = find_min_vertex(graph->vertices, dist, visited)))
	{
		p_name = parent[curr->index] ? parent[curr->index]->content : curr->content;
		printf("Checking %s, distance from %s is %d\n",
		       curr->content, p_name, dist[curr->index]);

		visited[curr->index] = 1;

		if (strcmp(curr->content, target->content) == 0)
			break;

		for (edge = curr->edges; edge; edge = edge->next)
		{
			if (visited[edge->dest->index])
				continue;

			new_dist = dist[curr->index] + edge->weight;
			if (new_dist < dist[edge->dest->index])
			{
				dist[edge->dest->index] = new_dist;
				parent[edge->dest->index] = curr;
			}
		}
	}
}

/**
 * dijkstra_graph - Computes shortest path across a graph using Dijkstra
 * @graph: Graph structure pointer wrapper
 * @start: Starting initialization node
 * @target: Goal target structure node
 *
 * Return: Allocated queue sequence pathway layout, or NULL on error
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	queue_t *path;
	int *dist;
	char *visited;
	vertex_t **parent;
	size_t i;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	dist = malloc(sizeof(int) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(char));
	parent = calloc(graph->nb_vertices, sizeof(vertex_t *));
	if (!path || !dist || !visited || !parent)
	{
		free(dist);
		free(visited);
		free(parent);
		if (path)
			queue_delete(path);
		return (NULL);
	}

	for (i = 0; i < graph->nb_vertices; i++)
		dist[i] = INT_MAX;
	dist[start->index] = 0;

	run_dijkstra(graph, dist, visited, parent, target);

	if (dist[target->index] == INT_MAX ||
	    !build_dijkstra_path(target, parent, path))
	{
		queue_delete(path);
		path = NULL;
	}

	free(dist);
	free(visited);
	free(parent);
	return (path);
}
