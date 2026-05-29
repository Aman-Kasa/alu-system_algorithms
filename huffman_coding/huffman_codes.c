#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * free_huffman_tree - Recursively deallocates all nodes and symbols in the tree
 * @root: Root node of the tree to free
 */
void free_huffman_tree(binary_tree_node_t *root)
{
	if (!root)
		return;

	free_huffman_tree(root->left);
	free_huffman_tree(root->right);

	if (root->data)
		free(root->data);
	free(root);
}

/**
 * traverse_and_print - Recursively crawls the Huffman tree to print codes
 * @root: Pointer to the current tree node
 * @code: Character buffer tracking the current path bits
 * @depth: Current depth index in the bit string
 */
void traverse_and_print(binary_tree_node_t *root, char *code, int depth)
{
	symbol_t *sym;

	if (!root)
		return;

	sym = (symbol_t *)root->data;

	if (!root->left && !root->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", sym->data, code);
		return;
	}

	if (root->left)
	{
		code[depth] = '0';
		traverse_and_print(root->left, code, depth + 1);
	}

	if (root->right)
	{
		code[depth] = '1';
		traverse_and_print(root->right, code, depth + 1);
	}
}

/**
 * huffman_codes - Builds a Huffman tree and prints codes for each symbol
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
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

	traverse_and_print(root, code_buffer, 0);

	/* Clean up everything completely to guarantee 0 bytes left in use */
	free(code_buffer);
	free_huffman_tree(root);

	return (1);
}
