#include "shell.h"

/**
 *compare_strings- compare two strings
 *@str: first string
 *@dest: second string to compare with
 *Return: difference of the two strings
 */

int compare_strings(char *str, char *dest)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] != dest[i])
			break;
		i++;
	}
	return (str[i] - dest[i]);
}

/**
 *concatenate_strings- concatenates two strings
 *@dest: string to be concatenated to
 *@src:  string to concatenate
 * Return: pointer to new string
 */

char *concatenate_strings(char *dest, char *src)
{
	char *new_string =  NULL;
	int len_dest = get_string_length(dest);
	int len_source = get_string_length(src);

	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	copy_string(dest, new_string);
	copy_string(src, new_string + len_dest);
	new_string[len_dest + len_source] = '\0';
	return (new_string);
}



/**
 *get_not_matching_prefix_length - get_not_matching_prefix_length
 *@str1: string to be searched
 *@str2: string to search for
 *
 *Return: index
 */


int get_not_matching_prefix_length(char *str1, char *str2)
{
	int len = 0, i;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (find_char(str2, str1[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 *get_prefix_length - gets the length of a prefix substring
 *@str1: string to be searched
 *@str2: string to search for
 *Return: number of bytes matched
 */
int get_prefix_length(char *str1, char *str2)
{
	int i = 0;
	int match = 0;

	while (str1[i] != '\0')
	{
		if (find_char(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}

/**
 *find_char - locates a char in a string
 *@s: string to be searched
 *@c: char to be checked
 *
 *Return: pointer to found char
 */

char *find_char(char *s, char c)
{
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
