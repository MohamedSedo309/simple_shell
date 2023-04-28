#include "shell.h"

/**
 *free_buff - frees memory bloC
 *@ptr: memory pointer
 *Return: 1 if freed, otherwise 0.
 */
int free_buff(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
