#include "shell.h"

/**
 * is_delimeter - check char if delimeter
 * @c: char
 * @delim: the delimeter string
 * Return: 1 or 0
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *is_interactive - check the shell mode
 *@info: struct address
 *Return: 1 interactive mode or 0 otherwise
 */
int is_interactive(infooo *info)
{
	return (isatty(STDIN_FILENO) && info->readfile <= 2);
}


/**
 * isalphabet - check alphabetic letter
 * @c: char
 * Return: 1 or 0
 */

int isalphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_str_to_int - convert string to int
 * @str: string
 * Return: 0 or converted int
 */

int convert_str_to_int(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
