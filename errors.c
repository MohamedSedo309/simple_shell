#include "shell.h"

/**
 *print_message_error - prints error msg
 *@str: error msg
 *Return: void
 */
void print_message_error(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_char(str[i]);
		i++;
	}
}

/**
 *echo_fd - put char to given file
 *@c: char
 *@fd: file
 *Return: 1 On succes
 */
int echo_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *print_char - print char
 *@c: char
 *Return: 1 On success
 */
int print_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}



/**
 *echo_string_fd - print string to file
 *@str: string
 *@fd: file
 *Return: char count
 */
int echo_string_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += echo_fd(*str++, fd);
	}
	return (i);
}
