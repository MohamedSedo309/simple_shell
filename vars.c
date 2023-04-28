#include "shell.h"

/**
 *check_if_chain - check for chain
 *@info: infooo struct
 *@buf: buffer
 *@p: current position
 *@i: starting position
 *@len: length
 *Return: Void
 */
void check_if_chain(infooo *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 *is_a_chain - test if is a chain delimeter
 *@info: infooo struct
 *@buff: the char buffer
 *@p: pointer to current position
 *Return: 1 or 0 otherwise
 */
int is_a_chain(infooo *info, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		info->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 *aliasreplace - replaces an aliases
 *@info: the parameter struct
 *Return: 1 if replaced or 0 otherwise
 */
int aliasreplace(infooo *info)
{
	int i;
	list_s *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = get_node_starter(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = find_char(node->str, '=');
		if (!p)
			return (0);
		p = duplicate_string(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 *replace_strrr - replaces string
 *@old: old string
 *@new: new string
 *Return: 1 if replaced, 0 otherwise
 */
int replace_strrr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 *var_replace - replaces vars
 *@info: infooo struct
 *Return: 1 if replaced, 0 otherwise
 */
int var_replace(infooo *info)
{
	int i = 0;
	list_s *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compare_strings(info->argv[i], "$?"))
		{
			replace_strrr(&(info->argv[i]),
					duplicate_string(conv_num(info->status, 10, 0)));
			continue;
		}
		if (!compare_strings(info->argv[i], "$$"))
		{
			replace_strrr(&(info->argv[i]),
					duplicate_string(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = get_node_starter(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_strrr(&(info->argv[i]),
					duplicate_string(find_char(node->str, '=') + 1));
			continue;
		}
		replace_strrr(&info->argv[i], duplicate_string(""));

	}
	return (0);
}
