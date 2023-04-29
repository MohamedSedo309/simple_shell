#include "shell.h"

/**
 *unset_alias - convert alias to string
 *@info: infooo struct
 *@str: the string alias
 *Return: 0 or 1
 */
int unset_alias(infooo *info, char *str)
{
	char *p, c;
	int ret;

	p = find_char(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_atindex(&(info->alias),
		get_node_arrange(info->alias, get_node_starter(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 *get_historyyyy - get the hitory of commands
 *@info: infoooo Structure
 *Return: 0
 */
int get_historyyyy(infooo *info)
{
	print_list_s(info->history);
	return (0);
}

/**
 *set_alias - convert alias to string
 *@info: infooo struct
 *@str:  alias
 *Return: 0 or 1
 */
int set_alias(infooo *info, char *str)
{
	char *p;

	p = find_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (create_end_node(&(info->alias), str, 0) == NULL);
}

/**
 *print_alias - print alias string
 *@node: alias node
 *Return: 0 or 1
 */
int print_alias(list_s *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = find_char(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		print_string(p + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * get_myalias - alias builtins (man alias)
 * @info: infooo Structure
 *  Return: Always 0
 */
int get_myalias(infooo *info)
{
	int i = 0;
	char *p = NULL;
	list_s *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = find_char(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(get_node_starter(info->alias, info->argv[i], '='));
	}

	return (0);
}
