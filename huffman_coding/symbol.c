#include <stdlib.h>
#include "huffman.h"

/**
 * symbol_create - Creates a symbol_t data structure
 * @data: Character to be stored
 * @freq: Associated frequency count
 *
 * Return: Pointer to the created structure, or NULL if it fails
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new_symbol;

	new_symbol = malloc(sizeof(symbol_t));
	if (new_symbol == NULL)
		return (NULL);

	new_symbol->data = data;
	new_symbol->freq = freq;

	return (new_symbol);
}
