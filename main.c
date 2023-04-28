#include "shell.h"

/**
 *main - entry point
 *@ac: arg count
 *@av: arg pointer
 *Return: on success 0 or 1 on error
 */
int main(int ac, char **av)
{
	infooo info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_message_error(av[0]);
				print_message_error(": 0: Can't open ");
				print_message_error(av[1]);
				print_char('\n');
				print_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfile = fd;
	}
	make_env_list(info);
	get_history_str(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
