#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * traverse_tree - Recursively traverses a Huffman tree to print codes
 * @root: Pointer to the current node
 * @code: Character buffer storing the current path ('0's and '1's)
 * @depth: Current depth in the tree (index in the buffer)
 */
void traverse_tree(binary_tree_node_t *root, char *code, int depth)
{
	symbol_t *sym;

	if (!root)
		return;

	sym = (symbol_t *)root->data;

	/* If it's a leaf node, print its data and code path */
	if (!root->left && !root->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", sym->data, code);
		return;
	}

	/* Go Left and append '0' */
	if (root->left)
	{
		code[depth] = '0';
		traverse_tree(root->left, code, depth + 1);
	}

	/* Go Right and append '1' */
	if (root->right)
	{
		code[depth] = '1';
		traverse_tree(root->right, code, depth + 1);
	}
}

/**
 * huffman_codes - Generates and prints the Huffman codes from a Huffman tree
 * @root: Pointer to the root node of the Huffman tree
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(binary_tree_node_t *root)
{
	char code_buffer[1024];

	if (!root)
		return (0);

	traverse_tree(root, code_buffer, 0);

	return (1);
}
