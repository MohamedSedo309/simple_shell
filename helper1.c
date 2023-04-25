#include "shell.h"

/**
 * tokin_maker - tokenizes input then stores it into an array
 *@_input: input to be parsed
 *@delim: delimiter to be used, needs to be one character string
 *
 *Return: tokens array
 */

char **tokin_maker(char *_input, char *delim)
{
int num_delim = 0;
char **av = NULL;
char *token = NULL;
char *save_ptr = NULL;
token = _strtok_r(_input, delim, &save_ptr);
while (token != NULL)
{
av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
av[num_delim] = token;
token = _strtok_r(NULL, delim, &save_ptr);
num_delim++;
}
av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
av[num_delim] = NULL;
return (av);
}

/**
 *print - prints a string to standerd output
 *@str: string to print
 *@stream: stream to print out to (stdout)
 *
 *Return: void
 */
void print(char *str, int stream)
{
int i;
for (i = 0; str[i] != '\0'; i++)
{
write(stream, &str[i], 1);
}
}

/**
 *remove_newline - remove new line from a string
 *@str: string to be used
 *Return: void
 */

void remove_newline(char *str)
{
int i = 0;
while (str[i] != '\0')
{
if (str[i] == '\n')
{
break;
}
i++;
}
str[i] = '\0';
}

/**
 *_strcpy - copy a string
 *@src: string to copy
 *@dest: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *src, char *dest)
{
int i = 0;
for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
}

/**
 *_strlen - get string length
 *@str: string
 * Return: string lenth
 */

int _strlen(char *str)
{
int len = 0;
if (str == NULL)
{
return (len);
}
for (len = 0; str[len] != '\0'; len++)
{
}
return (len);
}
