#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

/**
 * free_huffman_tree - Helper logic to free the generated huffman tree safely
 * @node: Root node of the tree
 */
void free_huffman_tree(binary_tree_node_t *node)
{
	if (!node)
		return;
	free_huffman_tree(node->left);
	free_huffman_tree(node->right);
	free(node->data);
	free(node);
}

/**
 * print_codes - Traverses tree recursively and generates code sequences
 * @root: Current binary tree node pointer
 * @code: Array tracking characters of the path string
 * @depth: Current depth index tracking path sequence
 */
void print_codes(binary_tree_node_t *root, char *code, int depth)
{
	if (!root)
		return;

	if (!root->left && !root->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", ((symbol_t *)root->data)->data, code);
		return;
	}

	if (root->left)
	{
		code[depth] = '0';
		print_codes(root->left, code, depth + 1);
	}
	if (root->right)
	{
		code[depth] = '1';
		print_codes(root->right, code, depth + 1);
	}
}

/**
 * huffman_codes - Builds the tree and prints the code allocations
 * @data: Array of characters
 * @freq: Array containing frequencies
 * @size: Size of input elements
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char *code_buffer;

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	code_buffer = malloc(sizeof(char) * (size + 1));
	if (!code_buffer)
	{
		free_huffman_tree(root);
		return (0);
	}

	print_codes(root, code_buffer, 0);

	free(code_buffer);
	free_huffman_tree(root);
	return (1);
}
