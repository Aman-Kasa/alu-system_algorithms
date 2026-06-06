#include <math.h>
#include "pathfinding.h"

/**
 * get_heuristic - Calculates Euclidean distance from a vertex to target vertex
 * @v: Current vertex
 * @target: Target destination vertex
 *
 * Return: Straight line distance as a double
 */
static double get_heuristic(vertex_t const *v, vertex_t const *target)
{
	double dx = v->x - target->x;
	double dy = v->y - target->y;

	return (sqrt((dx * dx) + (dy * dy)));
}

/**
 * find_min_f - Finds the unvisited vertex with the lowest f(v) score
 * @vertices: Head pointer to the overarching graph vertex list
 * @g_score: Array tracking exact cumulative costs from start
 * @f_score: Array tracking total estimated costs (g + h)
 * @visited: Array tracking vertex exploration status
 *
 * Return: Pointer to the optimal vertex, or NULL
 */
static vertex_t *find_min_f(vertex_t *vertices, int *g_score,
			    double *f_score, char *visited)
{
	vertex_t *min_v = NULL;
	vertex_t *curr;
	double min_f = INFINITY;

	for (curr = vertices; curr; curr = curr->next)
	{
		if (!visited[curr->index] && g_score[curr->index] != INT_MAX)
		{
			if (f_score[curr->index] < min_f)
			{
				min_f = f_score[curr->index];
				min_v = curr;
			}
		}
	}
	return (min_v);
}

/**
 * build_astar_path - Reconstructs the target trajectory path queue backwards
 * @target: End target destination vertex
 * @parent: Array referencing vertex ancestral history mapping
 * @path: Target sequence queue tracking path structure
 *
 * Return: 1 on success, 0 on failure
 */
static int build_astar_path(vertex_t const *target, vertex_t **parent,
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
 * run_astar - Core execution processing loop for A* graph search updates
 * @graph: Master tracking graph structure block wrapper
 * @g: Array tracking exact cumulative movement costs from start
 * @f: Array tracking total estimated costs (g + h)
 * @vis: Visited indices array tracking matrix map
 * @parent: Vertex parental ancestral tracking ledger matrix array
 * @target: Ultimate destination objective goal structural vertex
 */
static void run_astar(graph_t *graph, int *g, double *f,
		      char *vis, vertex_t **parent, vertex_t const *target)
{
	vertex_t *curr;
	edge_t *edge;
	int tent_g;
	char const *t_name;

	while ((curr = find_min_f(graph->vertices, g, f, vis)))
	{
		t_name = target->content;
		printf("Checking %s, distance to %s is %d\n",
		       curr->content, t_name, (int)get_heuristic(curr, target));

		vis[curr->index] = 1;

		if (strcmp(curr->content, target->content) == 0)
			break;

		for (edge = curr->edges; edge; edge = edge->next)
		{
			if (vis[edge->dest->index])
				continue;

			tent_g = g[curr->index] + edge->weight;
			if (tent_g < g[edge->dest->index])
			{
				parent[edge->dest->index] = curr;
				g[edge->dest->index] = tent_g;
				f[edge->dest->index] = tent_g +
					get_heuristic(edge->dest, target);
			}
		}
	}
}

/**
 * a_star_graph - Finds shortest path using the A* algorithm
 * @graph: Master tracking graph structure block wrapper
 * @start: Initial node source departure configuration
 * @target: Ultimate destination objective goal structural vertex
 *
 * Return: Allocated queue layout pathway tracing sequence, or NULL on failure
 */
queue_t *a_star_graph(graph_t *graph, vertex_t const *start,
		      vertex_t const *target)
{
	queue_t *path;
	int *g_score;
	double *f_score;
	char *visited;
	vertex_t **parent;
	size_t i;

	if (!graph || !start || !target)
		return (NULL);
	path = queue_create();
	g_score = malloc(sizeof(int) * graph->nb_vertices);
	f_score = malloc(sizeof(double) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(char));
	parent = calloc(graph->nb_vertices, sizeof(vertex_t *));
	if (!path || !g_score || !f_score || !visited || !parent)
	{
		free(g_score);
		free(f_score);
		free(visited);
		free(parent);
		if (path)
			queue_delete(path);
		return (NULL);
	}
	for (i = 0; i < graph->nb_vertices; i++)
	{
		g_score[i] = INT_MAX;
		f_score[i] = INFINITY;
	}
	g_score[start->index] = 0;
	f_score[start->index] = get_heuristic(start, target);
	run_astar(graph, g_score, f_score, visited, parent, target);
	if (g_score[target->index] == INT_MAX ||
	    !build_astar_path(target, parent, path))
	{
		queue_delete(path);
		path = NULL;
	}
	free(g_score);
	free(f_score);
	free(visited);
	free(parent);
	return (path);
}
