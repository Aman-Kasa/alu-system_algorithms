#include <stdlib.h>
#include "pathfinding.h"

queue_t *queue_create(void)
{
	queue_t *q = malloc(sizeof(queue_t));
	if (!q) return (NULL);
	q->front = NULL;
	q->rear = NULL;
	return (q);
}

queue_node_t *queue_push_front(queue_t *queue, void *ptr)
{
	queue_node_t *new_node;

	if (!queue) return (NULL);
	new_node = malloc(sizeof(queue_node_t));
	if (!new_node) return (NULL);

	new_node->ptr = ptr;
	new_node->next = queue->front;
	queue->front = new_node;
	if (!queue->rear)
		queue->rear = new_node;
	return (new_node);
}

void *dequeue(queue_t *queue)
{
	queue_node_t *temp;
	void *ptr;

	if (!queue || !queue->front) return (NULL);
	temp = queue->front;
	ptr = temp->ptr;
	queue->front = queue->front->next;
	if (!queue->front)
		queue->rear = NULL;
	free(temp);
	return (ptr);
}

void queue_delete(queue_t *queue)
{
	if (!queue) return;
	while (queue->front)
	{
		dequeue(queue);
	}
	free(queue);
}
