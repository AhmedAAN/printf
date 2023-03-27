#include "main.h"

/**
 * get_precision - Calculates the precision from a text
 * @format: The text we want to get the percision from
 * @i: Pointer to the location we are in
 * @list: The arguments
 * Return: Precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int counter = *i + 1;
	int pers = -1;

	if (format[counter] != '.')
	{
		return (pers);
	}

	pers = 0;

	for (counter += 1; format[counter] != '\0'; counter++)
	{
		if (is_digit(format[counter]))
		{
			precision *= 10;
			precision += format[counter] - 48;
		}
		else if (format[counter] == '*')
		{
			counter++;
			precision = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
	}
	*i = counter - 1;
}
