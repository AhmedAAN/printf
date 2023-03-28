#include "main.h"

/**
 * handle_print - Prints an argument based on its type.
 *
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: Index of the current format specifier in the format string.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier for the format string.
 * @precision: Precision specifier for the format string.
 * @size: Size specifier for the format string.
 *
 * Return: Number of characters printed, or -1 if an error occurs.
 */

int handle_print(const char *fmt, int *ind, va_list list, char buffer[], int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;

	/* Define an array of format specifier characters and their corresponding print functions */
	fmt_t fmt_types[] = {{'c', print_char}, {'s', print_string}, {'%', print_percent}, {'i', print_int}, {'d', print_int}, {'b', print_binary}, {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal}, {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable}, {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}};

	/* Loop over the array of format specifiers to find the appropriate print function */
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	{
		if (fmt[*ind] == fmt_types[i].fmt)
		{
			/* Call the matching print function with the provided arguments */
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
		}
	}

	/* If no matching print function was found, handle the unknown format specifier */
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
		{
			/* If the current character is the null terminator, return an error */
			return (-1);
		}

		/* Print the unknown character or a percent sign, depending on formatting options */
		unknow_len += write(1, "%%", 1);

		if (fmt[*ind - 1] == ' ')
		{
			/* If the previous character was a space, print a space as well */
			unknow_len += write(1, " ", 1);
		}
		else if (width)
		{/* If a width was specified, adjust the current index to skip over the unknown character and any previous flags */
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
			{
				--(*ind);
			}
			if (fmt[*ind] == ' ')
			{
				--(*ind);
			}
			return (1);
		} /* Print the unknown character */
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	} /* Return the number of characters printed */
	return (printed_chars);
}
