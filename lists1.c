#include "shell.h"

/**
 *get_list_str_part - get str from list_s
 *@head: head pointer
 *Return: strings array
 */
char **get_list_str_part(list_s *head)
{
	list_s *node = head;
	size_t i = getLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(get_string_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_string(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 *getLength - get Length of linked list
 *@head: head pointer
 *Return: list size
 */
size_t getLength(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}


/**
 *print_list_s - prints all list elements
 *@h: head pointer
 *Return: list length
 */
size_t print_list_s(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 *get_node_starter - get the node whose string
 *starts with strr
 *@node: node pointer
 *@strr: string to search
 *@c: the next char after strr
 *Return: match node or null
 */
list_s *get_node_starter(list_s *node, char *strr, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begain_with(node->str, strr);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 *get_node_arrange - gets node index
 *@head: head pointer
 *@node: node pointer
 *Return: index of node or -1
 */
ssize_t get_node_arrange(list_s *head, list_s *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
