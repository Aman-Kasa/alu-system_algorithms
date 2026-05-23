#include <stdlib.h>
#include "graphs.h"

/**
 * graph_delete - Completely deletes a graph structure.
 * @graph: Graph structure to destroy.
 */
void graph_delete(graph_t *graph)
{
	vertex_t *v_curr, *v_next;
	edge_t *e_curr, *e_next;

	if (!graph)
		return (0);

	v_curr = graph->vertices;
	while (v_curr)
	{
		v_next = v_curr->next;
		free(v_curr->content);

		e_curr = v_curr->edges;
		while (e_curr)
		{
			e_next = e_curr->next;
			free(e_curr);
			e_curr = e_next;
		}

		free(v_curr);
		v_curr = v_next;
	}
	free(graph);
}
