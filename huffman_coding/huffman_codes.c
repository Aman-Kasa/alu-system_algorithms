#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

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

	/* If it's a leaf node, terminate the string and print the code */
	if (!root->left && !root->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", sym->data, code);
		return;
	}

	/* Traverse Left path (append '0') */
	if (root->left)
	{
		code[depth] = '0';
		traverse_and_print(root->left, code, depth + 1);
	}

	/* Traverse Right path (append '1') */
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

	/* 1. Build the exact Huffman Tree using your stable builder */
	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	/* 2. Allocate a bit buffer safe for maximum theoretical tree depth */
	code_buffer = malloc(sizeof(char) * (size + 1));
	if (!code_buffer)
	{
		return (0);
	}

	/* 3. Run the organized leaf traversal printer */
	traverse_and_print(root, code_buffer, 0);

	/* 4. Clean up allocated path tracking structures */
	free(code_buffer);

	return (1);
}
