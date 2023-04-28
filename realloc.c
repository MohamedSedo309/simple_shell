#include "shell.h"

/**
 *set_memory - fills memory BloC
 *@s: pointer to memory Bloc
 *@c: byte to fill *s with
 *@n: bytes count
 *Return: (s) a pointer to the memory area s
 */
char *set_memory(char *s, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = c;
	return (s);
}

/**
 *_realloc_mem - reallocates a memory block
 *@ptr: pointer to old block
 *@old_size: byte size of old block
 *@new_size: byte size of new block
 *Return: pointer to da ol'block nameen.
 */
void *_realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * ffree_memory - frees a memory bloc
 * @mmm: string of strings
 */
void ffree_memory(char **mmm)
{
	char **a = mmm;

	if (!mmm)
		return;
	while (*mmm)
		free(*mmm++);
	free(a);
}
