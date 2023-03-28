#include "main.h"

/**
 * get_width - Calculates the width for printing
 *
 * @format: The string to print the arguments in
 * @i: Pointer to the current index in the string
 * @list: List of arguments
 * Return: Width to be used for printing
 */
int get_width(const char *format, int *i, va_list list)
{
	int pointer;
	int totalWidth = 0;

	/* Loop over the characters in the format starting from the current index */
	for (pointer = *i + 1; format[pointer] != '\0'; pointer++)
	{
		/* If the character is a digit, add it to the current width value */
		if (is_digit(format[pointer]))
		{
			totalWidth *= 10;
			totalWidth += format[pointer] - '0';
		}
		/*If the character is a wildcard, get the next argument in the list as the width value*/
		else if (format[pointer] == '*')
		{
			pointer++;
			totalWidth = va_arg(list, int);
			break;
		}
		/* If the character is not a digit or wildcard, stop processing */
		else
			break;
	}
	/* Update the current index pointer and return the calculated width value */
	*i = pointer - 1;

	return (totalWidth);
}
