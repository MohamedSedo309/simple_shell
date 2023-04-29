#include "shell.h"

/**
 *get_string_length - get string length
 *@str: the string
 *Return: length
 */
int get_string_length(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 *compare_strings - compare two strings
 *@s1: first string
 *@s2: second string
 *Return: compare
 */
int compare_strings(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 *concatenate_strings - concatenates two strings
 *@dest: destination
 *@src: source
 *Return: destination pointer
 */
char *concatenate_strings(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 *begain_with - checks if string start with
 *@search: string to search
 *@sub:substring to find
 *Return: address of next char of haystack or NULL
 */
char *begain_with(const char *search, const char *sub)
{
	while (*search)
		if (*search++ != *sub++)
			return (NULL);
	return ((char *)sub);
}
