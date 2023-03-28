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
	int prec = -1;

	if (format[counter] != '.')
	{
		return (prec);
	}

	prec = 0;

	for (counter += 1; format[counter] != '\0'; counter++)
	{
		if (is_digit(format[counter]))
		{
			prec *= 10;
			prec += format[counter] - 48;
		}
		else if (format[counter] == '*')
		{
			counter++;
			prec = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
	}
	*i = counter - 1;

	return (prec);
}
