#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>

/* Provided Queue library interface structures */
typedef struct queue_node_s
{
	void *ptr;
	struct queue_node_s *next;
} queue_node_t;

typedef struct queue_s
{
	queue_node_t *front;
	queue_node_t *rear;
} queue_t;

/* Provided utility functions from -lqueues */
queue_t *queue_create(void);
queue_node_t *queue_push_front(queue_t *queue, void *ptr);
queue_node_t *queue_push_back(queue_t *queue, void *ptr);
void *dequeue(queue_t *queue);
void queue_delete(queue_t *queue);

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

/* Task 0 Prototype */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);

#endif /* PATHFINDING_H */
