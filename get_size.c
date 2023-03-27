#include "main.h"

/**
 * get_size - Calculates the size of the argument
 * @format: The string
 * @i: Pointer to the location in the string
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int pointer = *i + 1;
	int size = 0;

	if (format[pointer] == 'l')
		size = S_LONG;
	else if (format[pointer] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = pointer - 1;
	else
		*i = pointer;

	return (size);
}
