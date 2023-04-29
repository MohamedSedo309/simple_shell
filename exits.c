#include "shell.h"

/**
 **copy_string2 - copy a string
 *@dest:destination
 *@src:  source
 *@n: char count
 *Return: string
 */
char *copy_string2(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **find_char - search for char in  string
 *@str: str
 *@c: char
 *Return: memory pointer
 */
char *find_char(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 **concatenate_strings2 - concatenate strings
 *@dest: destniation
 *@src: source
 *@n: cunmber of bytes
 *Return: the concatenated string
 */
char *concatenate_strings2(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
