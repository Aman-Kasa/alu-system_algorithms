#include <stdlib.h>
#include "graphs.h"

/**
 * struct queue_s - Basic node wrapper for parsing BFS queues.
 * @vertex: Targeted vertex element.
 * @depth: Height coordinate track trace.
 * @next: Pointer targeting next segment.
 */
typedef struct queue_s
{
	const vertex_t *vertex;
	size_t depth;
	struct queue_s *next;
} queue_t;

/**
 * breadth_first_traverse - Tracks layers cleanly via FIFO loop sequences.
 * @graph: Target graph mapping structure.
 * @action: Function code segment targeting items.
 *
 * Return: Final recorded execution height level.
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t global_max = 0;
	queue_t *head = NULL, *tail = NULL, *temp = NULL;
	edge_t *edge = NULL;

	if (!graph || !action || !graph->vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (0);
	head = malloc(sizeof(*head));
	if (!head)
	{
		free(visited);
		return (0);
	}
	head->vertex = graph->vertices;
	head->depth = 0;
	head->next = NULL;
	tail = head;
	visited[graph->vertices->index] = 1;
	while (head)
	{
		const vertex_t *curr = head->vertex;
		size_t curr_depth = head->depth;

		action(curr, curr_depth);
		if (curr_depth > global_max)
			global_max = curr_depth;
		edge = curr->edges;
		while (edge)
		{
			if (!visited[edge->dest->index])
			{
				queue_t *new_node = malloc(sizeof(*new_node));

				if (!new_node)
				{
					while (head)
					{
						temp = head->next;
						free(head);
						head = temp;
					}
					free(visited);
					return (0);
				}
				new_node->vertex = edge->dest;
				new_node->depth = curr_depth + 1;
				new_node->next = NULL;
				tail->next = new_node;
				tail = new_node;
				visited[edge->dest->index] = 1;
			}
			edge = edge->next;
		}
		temp = head->next;
		free(head);
		head = temp;
	}
	free(visited);
	return (global_max);
}
