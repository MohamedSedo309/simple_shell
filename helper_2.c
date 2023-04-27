#include "shell.h"

/**
 *tokenize_string_r - tokenizes a string
 *@string: string to tokenize
 *@done: delimiter to use in tokenizing the string
 *@save_pointerr: pointer to track the string
 *of the next token
 *Return: The next available token
 */
char *tokenize_string_r(char *string, char *done, char **save_pointerr)
{
	char *end;

	if (string == NULL)
		string = *save_pointerr;

	if (*string == '\0')
	{
		*save_pointerr = string;
		return (NULL);
	}

	string += get_prefix_length(string, done);
	if (*string == '\0')
	{
		*save_pointerr = string;
		return (NULL);
	}

	end = string + get_not_matching_prefix_length(string, done);
	if (*end == '\0')
	{
		*save_pointerr = end;
		return (string);
	}

	*end = '\0';
	*save_pointerr = end + 1;
	return (string);
}

/**
 *convert_string_to_integer - convert string to int
 *@s: the string to convert
 *Return: the converted int
 */
int convert_string_to_integer(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 *reallocate_memory - reallocate a memory block
 *@pointerr: pointer to the memory previously
 *allocated with a call to malloc
 *@os: size of ptr (old)
 *@ns: size of the new memory
 *Return: pointer to the address of the new memory block
 */
void *reallocate_memory(void *pointerr, unsigned int os, unsigned int ns)
{
	void *tb;
	unsigned int i;

	if (pointerr == NULL)
	{
		tb = malloc(ns);
		return (tb);
	}
	else if (ns == os)
		return (pointerr);
	else if (ns == 0 && pointerr != NULL)
	{
		free(pointerr);
		return (NULL);
	}
	else
	{
		tb = malloc(ns);
		if (tb != NULL)
		{
			for (i = 0; i < new_min(os, ns); i++)
				*((char *)tb + i) = *((char *)pointerr + i);
			free(pointerr);
			return (tb);
		}
		else
			return (NULL);

	}
}

/**
 *ctrl_c_signal_handler - handles the CTRL-C key
 *@signum: signal number
 *Return: void
 */
void ctrl_c_signal_handler(int sgn)
{
	if (sgn == SIGINT)
		print_message("\n($) ", STDIN_FILENO);
}

/**
 *remove_comments - ignore everything after a '#'
 *@innn: input to be used
 *
 *Return: void
 */
void remove_comments(char *innn)
{
	int i = 0;

	if (innn[i] == '#')
		innn[i] = '\0';
	while (innn[i] != '\0')
	{
		if (innn[i] == '#' && innn[i - 1] == ' ')
			break;
		i++;
	}
	innn[i] = '\0';
}
