#include "pathfinding.h"

/**
 * append_to_path - Helper to allocate a point and prepend it to the queue path
 * @path: Queue tracking the successful path sequence
 * @x: X coordinate
 * @y: Y coordinate
 *
 * Return: 1 on success, 0 on failure
 */
int append_to_path(queue_t *path, int x, int y)
{
	point_t *step = malloc(sizeof(point_t));

	if (!step)
		return (0);
	step->x = x;
	step->y = y;
	queue_push_front(path, step);
	return (1);
}

/**
 * backtrack_recursive - Helper function executing recursive pathfinding
 * @map: Pointer to a read-only 2D array representing the map
 * @rows: Total number of rows
 * @cols: Total number of columns
 * @curr: Current coordinates being explored
 * @target: Target point coordinates
 * @visited: 2D array indicating visited positions
 * @path: Queue tracking the successful path sequence
 *
 * Return: 1 if path found, 0 otherwise
 */
int backtrack_recursive(char **map, int rows, int cols, point_t const *curr,
			point_t const *target, char **visited, queue_t *path)
{
	point_t neighbors[4];
	int i;

	if (curr->x < 0 || curr->x >= cols || curr->y < 0 || curr->y >= rows)
		return (0);
	if (map[curr->y][curr->x] == '1' || visited[curr->y][curr->x] == 1)
		return (0);

	printf("Checking coordinates [%d, %d]\n", curr->x, curr->y);
	visited[curr->y][curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
		return (append_to_path(path, curr->x, curr->y));

	/* Ordered exploration direction: RIGHT, BOTTOM, LEFT, TOP */
	neighbors[0] = (point_t){curr->x + 1, curr->y};
	neighbors[1] = (point_t){curr->x, curr->y + 1};
	neighbors[2] = (point_t){curr->x - 1, curr->y};
	neighbors[3] = (point_t){curr->x, curr->y - 1};

	for (i = 0; i < 4; i++)
	{
		if (backtrack_recursive(map, rows, cols, &neighbors[i],
					target, visited, path))
			return (append_to_path(path, curr->x, curr->y));
	}

	return (0);
}

/**
 * free_visited - Helper to free the visited tracking matrix
 * @visited: 2D matrix array to free
 * @allocated_rows: Number of rows successfully allocated
 */
void free_visited(char **visited, int allocated_rows)
{
	int i;

	for (i = 0; i < allocated_rows; i++)
		free(visited[i]);
	free(visited);
}

/**
 * backtracking_array - Finds the first viable path using backtracking
 * @map: Pointer to a read-only 2D array
 * @rows: Number of rows of map
 * @cols: Number of columns of map
 * @start: Target starting point
 * @target: End objective target point
 *
 * Return: Pointer to queue path trajectory sequence, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path;
	char **visited;
	int i, status;

	if (!map || !start || !target || rows <= 0 || cols <= 0)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = malloc(sizeof(char *) * rows);
	if (!visited)
	{
		free(path);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
		{
			free_visited(visited, i);
			free(path);
			return (NULL);
		}
	}

	status = backtrack_recursive(map, rows, cols, start, target, visited, path);
	free_visited(visited, rows);

	if (status == 0)
	{
		queue_delete(path);
		return (NULL);
	}

	return (path);
}
