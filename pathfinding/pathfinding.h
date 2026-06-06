#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 * enum edge_type_e - Defines graph edge directionality type rules
 * @UNIDIRECTIONAL: Single-directional connection
 * @BIDIRECTIONAL: Two-way connection
 */
typedef enum edge_type_e
{
	UNIDIRECTIONAL,
	BIDIRECTIONAL
} edge_type_t;

/**
 * struct queue_node_s - Node of a queue structure
 *
 * @ptr: Pointer to data stored in the node
 * @next: Pointer to the next node in the queue
 */
typedef struct queue_node_s
{
	void *ptr;
	struct queue_node_s *next;
} queue_node_t;

/**
 * struct queue_s - Queue management wrapper structure
 *
 * @front: Pointer to the front node of the queue
 * @rear: Pointer to the rear node of the queue
 */
typedef struct queue_s
{
	queue_node_t *front;
	queue_node_t *rear;
} queue_t;

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * struct edge_s - Connection between vertices
 *
 * @dest: Pointer to the destination vertex
 * @weight: Weight of the edge connection
 * @next: Pointer to the next edge in the adjacency list
 */
typedef struct edge_s
{
	struct vertex_s *dest;
	int weight;
	struct edge_s *next;
} edge_t;

/**
 * struct vertex_s - Graph vertex node representation
 *
 * @index: Index of the vertex
 * @content: String description data (e.g. city name)
 * @x: X coordinate mapping value
 * @y: Y coordinate mapping value
 * @edges: Linked list pointer to adjacent target edges
 * @next: Next vertex pointer in the overarching graph list
 */
typedef struct vertex_s
{
	size_t index;
	char *content;
	int x;
	int y;
	edge_t *edges;
	struct vertex_s *next;
} vertex_t;

/**
 * struct graph_s - Master tracking graph structure wrapper
 *
 * @nb_vertices: Total count tracking vertices
 * @vertices: Head pointer to the chain list of vertices
 */
typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t *vertices;
} graph_t;

/* Library utility prototypes from -lqueues and -lgraphs */
queue_t *queue_create(void);
queue_node_t *queue_push_front(queue_t *queue, void *ptr);
void *dequeue(queue_t *queue);
void queue_delete(queue_t *queue);

graph_t *graph_create(void);
vertex_t *graph_add_vertex(graph_t *graph, char const *content, int x, int y);
int graph_add_edge(graph_t *graph, char const *src, char const *dest,
		   int weight, edge_type_t type);
void graph_delete(graph_t *graph);

/* Task 0: Backtracking - Array */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);

/* Task 1: Backtracking - Graph */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target);

/* Task 2: Dijkstra's - Graph */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target);

/* Task 3: A* - Graph */
queue_t *a_star_graph(graph_t *graph, vertex_t const *start,
		      vertex_t const *target);

#endif /* PATHFINDING_H */
