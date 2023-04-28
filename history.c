#include "shell.h"

/**
 *get_ffhistory - returns the history file
 *@info: infooo struct
 *Return: get history file location
 */

char *get_ffhistory(infooo *info)
{
	char *buff, *dirr;

	dirr = get_enviroment(info, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (get_string_length(dirr) + get_string_length(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	copy_string(buff, dirr);
	concatenate_strings(buff, "/");
	concatenate_strings(buff, HIST_FILE);
	return (buff);
}

/**
 *print_hiss - creates a file or open
 *to an existing file
 *@info: infooo struct
 *Return: 1 on success,-1 on fail
 */
int print_hiss(infooo *info)
{
	ssize_t fd;
	char *fname = get_ffhistory(info);
	list_s *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		echo_string_fd(node->str, fd);
		echo_fd('\n', fd);
	}
	echo_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 *get_history_str - reads history from
 *the history file
 *@info: infooo struct
 *Return: history count or 0 otherwise
 */
int get_history_str(infooo *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_ffhistory(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			hiss_list_builder(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		hiss_list_builder(info, buff + last, linecount++);
	free(buff);
	info->histcounter = linecount;
	while (info->histcounter-- >= HIST_MAX)
		delete_atindex(&(info->history), 0);
	include_hist(info);
	return (info->histcounter);
}

/**
 *hiss_list_builder - build history list
 *@info: infooo Structure arguments
 *@buf: buffer
 *@linecounter: the history lines counter
 *Return: Always 0
 */
int hiss_list_builder(infooo *info, char *buf, int linecounter)
{
	list_s *node = NULL;

	if (info->history)
		node = info->history;
	create_end_node(&node, buf, linecounter);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 *include_hist - numbers the history of linked list
 *@info: infoo Structure
 *Return: history count
 */
int include_hist(infooo *info)
{
	list_s *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcounter = i);
}
