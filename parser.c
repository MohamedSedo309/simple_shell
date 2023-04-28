#include "shell.h"

/**
 * is_a_cmd - check if a file is an executable command
 * @info: infoooo struct
 * @path: file path
 *
 * Return: 1 if true or 0 .
 */
int is_a_cmd(infooo *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 *get_path - get command path
 *@info: infoooo struct
 *@pathstrr: the PATH
 *@cmd: command to find
 *Return: full path of cmd if found or NULL
 */
char *get_path(infooo *info, char *pathstrr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstrr)
		return (NULL);
	if ((get_string_length(cmd) > 2) && begain_with(cmd, "./"))
	{
		if (is_a_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrr[i] || pathstrr[i] == ':')
		{
			path = duplicate_char(pathstrr, curr_pos, i);
			if (!*path)
				concatenate_strings(path, cmd);
			else
			{
				concatenate_strings(path, "/");
				concatenate_strings(path, cmd);
			}
			if (is_a_cmd(info, path))
				return (path);
			if (!pathstrr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 *duplicate_char - duplicates chars
 *@pathstr: the PATH string
 *@start: starting pos
 *@stop: end pos
 *Return: string pointer
 */
char *duplicate_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
