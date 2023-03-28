#include "main.h"

/**
 * is_printable - Determines if a character is printable
 * @c: The character to evaluate
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127) /* Printable ASCII range */
		return (1);

	return (0);
}

/**
 * append_hexa_code - Appends ASCII in hexadecimal code to a buffer
 * @buffer: Array of characters to append to
 * @i: Index at which to start appending
 * @ascii_code: ASCII code to convert and append
 *
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF"; /* Hexadecimal map */

	/* Convert ASCII code to hexadecimal format */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\'; /* First escape character */
	buffer[i++] = 'x'; /* Second escape character */

	/* Append the two-digit hexadecimal code */
	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3); /* Return length of appended characters */
}

/**
 * is_digit - Determines if a character is a digit
 * @c: The character to evaluate
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9') /* Digit ASCII range */
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @num: The number to cast
 * @size: The size to cast to (S_LONG, S_SHORT, S_INT)
 *
 * Return: The casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG) /* Cast to long integer */
		return (num);
	else if (size == S_SHORT) /* Cast to short integer */
		return ((short)num);

	return ((int)num); /* Cast to regular integer */
}

/**
 * convert_size_unsgnd - Casts an unsigned number to the specified size
 * @num: The number to cast
 * @size: The size to cast to (S_LONG, S_SHORT, S_INT)
 *
 * Return: The casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG) /* Cast to unsigned long integer */
		return (num);
	else if (size == S_SHORT) /* Cast to unsigned short integer */
		return ((unsigned short)num);

	return ((unsigned int)num); /* Cast to unsigned regular integer */
}
