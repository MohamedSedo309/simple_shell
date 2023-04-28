#include "shell.h"

/**
 *create_end_node - adds a node to the end of the list
 *@head: head pointer
 *@str: string field
 *@num: index
 *Return: size of list
 */
list_s *create_end_node(list_s **head, const char *str, int num)
{
	list_s *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);
	set_memory((void *)new_node, 0, sizeof(list_s));
	new_node->num = num;
	if (str)
	{
		new_node->str = duplicate_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 *create_node - adds node to start of list
 *@head: head pointer
 *@str: str field of node
 *@num: node index
 *Return: list size
 */
list_s *create_node(list_s **head, const char *str, int idx)
{
	list_s *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_s));
	if (!new_head)
		return (NULL);
	set_memory((void *)new_head, 0, sizeof(list_s));
	new_head->num = idx;
	if (str)
	{
		new_head->str = duplicate_string(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 *print_str_part - prints str of list_s linked list
 *@head: head pointer
 *Return: list length
 */
size_t print_str_part(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		print_string(head->str ? head->str : "(nil)");
		print_string("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 *freemem_list - frees list nodes
 *@head_ptr: head pointer
 *Return: void
 */
void freemem_list(list_s **head_ptr)
{
	list_s *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 *delete_atindex - deletes node atindex
 *@head: head pointer
 *@idx: index to delete
 *Return: 1 on success, 0 on failure
 */
int delete_atindex(list_s **head, unsigned int idx)
{
	list_s *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
