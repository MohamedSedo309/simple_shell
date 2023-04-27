#include "shell.h"

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
