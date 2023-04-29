#include "shell.h"

/**
 * copy_env_string - copy_env_string
 * @info: infooo Structure
 * Return: 0
 */
char **copy_env_string(infooo *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = get_list_str_part(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 *remove_env_var - delete env
 *@info: infooo Structure
 *Return: 1 or 0
 *@var: env var
 */
int remove_env_var(infooo *info, char *var)
{
	list_s *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begain_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_atindex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 *make_env - Initialize environment var
 *@info: infooo Structure
 *@var: the string env var property
 *@value: the string env var value
 *Return: Always 0
 */
int make_env(infooo *info, char *var, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(get_string_length(var) + get_string_length(value) + 2);
	if (!buf)
		return (1);
	copy_string(buf, var);
	concatenate_strings(buf, "=");
	concatenate_strings(buf, value);
	node = info->env;
	while (node)
	{
		p = begain_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	create_end_node(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
