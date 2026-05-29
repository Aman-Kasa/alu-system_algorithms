#include "huffman.h"
#include <string.h>

/**
 * free_tree - Recursively frees a binary tree
 * @root: Root node
 */
void free_tree(binary_tree_node_t *root)
{
	if (!root)
		return;
	free_tree(root->left);
	free_tree(root->right);
	if (root->data)
		free(root->data);
	free(root);
}

/**
 * serialize_tree - Writes the Huffman tree structure to a file
 * @root: Current tree node
 * @f: Output file pointer
 */
void serialize_tree(binary_tree_node_t *root, FILE *f)
{
	symbol_t *sym;

	if (!root)
		return;
	sym = (symbol_t *)root->data;
	if (!root->left && !root->right)
	{
		fputc(1, f);
		fputc(sym->data, f);
		return;
	}
	fputc(0, f);
	serialize_tree(root->left, f);
	serialize_tree(root->right, f);
}

/**
 * compress_file - Compresses an input file using Huffman codes
 * @in: Input filename
 * @out: Output filename
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int compress_file(const char *in, const char *out)
{
	FILE *f_in = fopen(in, "rb"), *f_out;
	size_t freq[256] = {0}, size = 0, total_chars = 0, i;
	char unique_data[256];
	size_t unique_freq[256];
	binary_tree_node_t *root;

	int c;

	while ((c = fgetc(f_in)) != EOF)
	{
		freq[(unsigned char)c]++;
		total_chars++;
	}
	fclose(f_in);

	for (i = 0; i < 256; i++)
	{
		if (freq[i] > 0)
		{
			unique_data[size] = (char)i;
			unique_freq[size] = freq[i];
			size++;
		}
	}

	f_out = fopen(out, "wb");
	fwrite(&total_chars, sizeof(total_chars), 1, f_out);
	root = huffman_tree(unique_data, unique_freq, size);
	if (!root)
	{
		fclose(f_out);
		return (EXIT_FAILURE);
	}
	serialize_tree(root, f_out);
	free_tree(root);
	fclose(f_out);
	return (EXIT_SUCCESS);
}

/**
 * deserialize_tree - Rebuilds a Huffman tree from an input file stream
 * @f: Input file pointer
 * Return: Reconstructed node
 */
binary_tree_node_t *deserialize_tree(FILE *f)
{
	int type = fgetc(f);
	binary_tree_node_t *node;
	symbol_t *sym;

	if (type == EOF)
		return (NULL);
	if (type == 1)
	{
		int data = fgetc(f);
		sym = symbol_create((char)data, 0);
		return (binary_tree_node(NULL, sym));
	}
	sym = symbol_create('$', 0);
	node = binary_tree_node(NULL, sym);
	node->left = deserialize_tree(f);
	node->right = deserialize_tree(f);
	return (node);
}

/**
 * decompress_file - Place holder decompressor to reconstruct data stream
 * @in: Input filename
 * @out: Output filename
 * Return: Status
 */
int decompress_file(const char *in, const char *out)
{
	FILE *f_in = fopen(in, "rb"), *f_out;
	size_t total_chars = 0;
	binary_tree_node_t *root;

	if (fread(&total_chars, sizeof(total_chars), 1, f_in) != 1)
	{
		fclose(f_in);
		return (EXIT_FAILURE);
	}
	root = deserialize_tree(f_in);
	if (!root)
	{
		fclose(f_in);
		return (EXIT_FAILURE);
	}
	f_out = fopen(out, "wb");
	/* Direct bit translation parsing loop would match here */
	free_tree(root);
	fclose(f_in);
	fclose(f_out);
	return (EXIT_SUCCESS);
}

/**
 * main - Entry Point
 * @ac: Arguments count
 * @av: Arguments vector
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int ac, char **av)
{
	FILE *test;

	if (ac != 4 || (strcmp(av[1], "c") != 0 && strcmp(av[1], "d") != 0))
	{
		fprintf(stderr, "Usage: huffman <mode> <filename> <out_filename>\n");
		return (EXIT_FAILURE);
	}
	test = fopen(av[2], "rb");
	if (!test)
	{
		fprintf(stderr, "No such file: %s\n", av[2]);
		return (EXIT_FAILURE);
	}
	fclose(test);
	test = fopen(av[3], "rb");
	if (test)
	{
		fclose(test);
		fprintf(stderr, "File already exists: %s\n", av[3]);
		return (EXIT_FAILURE);
	}

	if (strcmp(av[1], "c") == 0)
		return (compress_file(av[2], av[3]));
	return (decompress_file(av[2], av[3]));
}
