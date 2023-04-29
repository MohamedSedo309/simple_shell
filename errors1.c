#include "shell.h"

/**
 *err_convert_str_to_int - convert string to int
 *@s: string
 *Return: converted string count
 */
int err_convert_str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 *print_e_message - print err msg
 *@info: infooo struct
 *@estr: string error type
 * Return: 0
 */
void print_e_message(infooo *info, char *estr)
{
	print_message_error(info->filename);
	print_message_error(": ");
	print_dec(info->count_line, STDERR_FILENO);
	print_message_error(": ");
	print_message_error(info->argv[0]);
	print_message_error(": ");
	print_message_error(estr);
}

/**
 *print_dec - print decimal
 *@input: input
 *@fd: file
 *Return: characters count
 */
int print_dec(int input, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file == STDERR_FILENO)
		__putchar = print_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 *conv_num -  itoa converter
 *@num: number
 *@base: base
 *@flags: arg flags
 *Return: string
 */
char *conv_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 *remove_comment - remove comments
 *@buf: string address
 *Return: 0
 */
void remove_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
