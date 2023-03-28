#include "main.h"

/**
 * get_flags - Get the active flags
 * @format: The string we work on
 * @i: A pointer to the location inside the text
 * Return: Return Flagtotal
 */
int get_flags(const char *format, int *i)
{
	int oCounter, iCounter, flagTotal = 0;
	const char flags[] = {'-', '+', '0', '#', ' ', '\0'};
	const int flags_values[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (oCounter = *i + 1; format[oCounter] != '\0'; oCounter++)
	{
		for (iCounter = 0; flags[iCounter] != '\0'; iCounter++)
		{
			if (format[oCounter] == flags[iCounter])
			{
				flagTotal |= flags_values[iCounter];
				break;
			}
		}
		if (flags[iCounter] == 0)
		{
			break;
		}
	}
	*i = oCounter - 1;

	return (flagTotal);
}
