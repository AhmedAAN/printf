#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handle_write_char - Prints a character with padding and alignment options
 * @c: The character to be printed
 * @buffer: The buffer array to handle the print
 * @flags: The flags that determine whether to use padding and alignment
 * @width: The minimum width of the printed output, with padding if necessary
 * @precision: The precision specifier (unused in this function)
 * @size: The size specifier (unused in this function)
 *
 * Return: The number of characters printed
 */

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	/* char is stored at left and padding at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';

		/* Add padding to the buffer */
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		/* Print the character with or without padding */
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	/* If no padding is needed, print the character directly */
	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/

/**
 * write_number - Prints a number with padding and alignment options
 * @is_negative: Whether the number is negative (1) or not (0)
 * @ind: The index of the buffer array to start printing the number from
 * @buffer: The buffer array to handle the print
 * @flags: The flags that determine whether to use padding and alignment
 * @width: The minimum width of the printed output, with padding if necessary
 * @precision: The precision specifier (unused in this function)
 * @size: The size specifier (unused in this function)
 *
 * Return: The number of characters printed
 */

int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	/* Determine the extra character to print (sign or space) */
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	/* Call write_num to handle the printing and padding of the number */
	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a buffer with padding and alignment options
 * @ind: The index at which the number starts in the buffer
 * @buffer: The buffer array to handle the print
 * @flags: The flags that determine whether to use padding and alignment
 * @width: The minimum width of the printed output, with padding if necessary
 * @prec: The precision specifier
 * @length: The length of the number to be printed
 * @padd: The padding character to be used
 * @extra_c: An extra character to be printed (sign or space)
 *
 * Return: The number of characters printed
 */

int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	/* Handle special case where number is 0 with precision 0 */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);

	/* Handle special case where number is 0 with non-zero precision */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';

	/* Pad the number with zeroes if necessary */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;

	/* Add an extra character (sign or space) if necessary */
	if (extra_c != 0)
		length++;

	/* Add padding if necessary */
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}

	/* Add extra character (sign or space) if necessary and print the number */
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number with padding and alignment options
 * @is_negative: A number indicating if the number is negative (unused)
 * @ind: The index at which the number starts in the buffer
 * @buffer: The buffer array to handle the print
 * @flags: The flags that determine whether to use padding and alignment
 * @width: The minimum width of the printed output, with padding if necessary
 * @precision: The precision of the printed output, with padding if necessary
 * @size: The size specifier (unused)
 *
 * Return: The number of characters printed
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	/* Unused parameters */
	UNUSED(is_negative);
	UNUSED(size);

	/* Handle special case where precision is zero and value is zero */
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	/* Add padding if necessary */
	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer > padd] */
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to left of padding [padd > buffer] */
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	/* No padding needed */
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address with padding and alignment options
 * @buffer: The buffer array to handle the print
 * @ind: The index at which the number starts in the buffer
 * @length: The length of the number to be printed
 * @width: The minimum width of the printed output, with padding if necessary
 * @flags: The flags that determine whether to use padding and alignment
 * @padd: The padding character to be used
 * @extra_c: An extra character to be printed (sign or space)
 * @padd_start: The index at which padding should start
 *
 * Return: The number of characters printed
 */

int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	/* Add padding if necessary */
	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}

	/* No padding needed */
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
