#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * print_codes_recursive - Traverses the Huffman tree to print character codes
 * @root: Pointer to the current node in the Huffman tree
 * @buffer: Buffer array to accumulate path string characters
 * @depth: Current depth level within the traversal path
 */
void print_codes_recursive(binary_tree_node_t *root, char *buffer, int depth)
{
	symbol_t *sym;

	if (!root)
		return;

	sym = (symbol_t *)root->data;

	/* Leaf node validation check */
	if (!root->left && !root->right)
	{
		buffer[depth] = '\0';
		if (sym && sym->data != '$' && sym->data != -1)
			printf("%c: %s\n", sym->data, buffer);
		return;
	}

	/* Go left: Append '0' */
	if (root->left)
	{
		buffer[depth] = '0';
		print_codes_recursive(root->left, buffer, depth + 1);
	}

	/* Go right: Append '1' */
	if (root->right)
	{
		buffer[depth] = '1';
		print_codes_recursive(root->right, buffer, depth + 1);
	}
}

/**
 * free_huffman_tree_nodes - Performs depth-first manual memory cleanups
 * @root: Pointer to the current active tree node element
 */
void free_huffman_tree_nodes(binary_tree_node_t *root)
{
	if (!root)
		return;

	free_huffman_tree_nodes(root->left);
	free_huffman_tree_nodes(root->right);

	if (root->data)
		free(root->data);
	free(root);
}

/**
 * huffman_codes - Builds a Huffman tree and prints codes for each symbol
 * @data: Array of characters of size size
 * @freq: Array containing the associated frequencies
 * @size: Size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char *buffer;

	if (!data || !freq || size == 0)
		return (0);

	/* Build the complete Huffman tree from components */
	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	/* Allocate a traversal code path layout buffer (max depth is size) */
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
	{
		free_huffman_tree_nodes(root);
		return (0);
	}

	/* Walk the tree and print the final codes */
	print_codes_recursive(root, buffer, 0);

	/* Clean up all memory allocations to satisfy Valgrind */
	free(buffer);
	free_huffman_tree_nodes(root);

	return (1);
}
