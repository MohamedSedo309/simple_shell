#include "shell.h"

/**
 *input_buf - input buffer
 *@info: infooo struct
 *@buf: buffer
 *@len: length
 *Return: bytes count
 */
ssize_t input_buf(infooo *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		
		free(*buf);
		*buf = NULL;
		signal(SIGINT, ctrl_c_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = line_getter(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->conutline_flag = 1;
			remove_comment(*buf);
			hiss_list_builder(info, *buf, info->histcounter++);
			{
				*len = r;
				info->cmd_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * input_getter - gets a line minus the newline
 * @info: infooo struct
 *
 * Return: bytes read
 */
ssize_t input_getter(infooo *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_if_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_a_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buffer_type = CMD_NORM;
		}

		*buf_p = p;
		return (get_string_length(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: infooo struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(infooo *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfile, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * line_getter - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr:pointer to bufferL
 * @length:legth of buffer
 * Return: string
 */
int line_getter(infooo *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = find_char(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc_mem(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		concatenate_strings2(new_p, buf + i, k - i);
	else
		copy_string2(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 *ctrl_c_handler - ctrl-C handler
 *@sig_num: signal number
 *Return: void
 */
void ctrl_c_handler(__attribute__((unused))int sig_num)
{
	print_string("\n");
	print_string("$ ");
	_putchar(BUF_FLUSH);
}
