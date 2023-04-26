#include "shell.h"
char **tokenize_string(char *input_string, char *done)
{
	int num_done = 0;
	char **now = NULL;
	char *tk = NULL;
	char *pointer_s = NULL;

	tk = tokenize_string_r(input_string, done, &pointer_s);

	while (tk != NULL)
	{
		noww = reallocate_memory(noww, sizeof(*noww) * num_done, sizeof(*noww) * (num_done + 1));
		noww[num_done] = tk;
		tk = tokenize_string_r(NULL, done, &pointer_s);
		num_done++;
	}

	noww = reallocate_memory(noww, sizeof(*noww) * num_done, sizeof(*noww) * (num_done + 1));
	noww[num_done] = NULL;

	return (noww);
}

void print_message(char *string, int stream)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}

void remove_newline_character(char *str)
{
	int f = 0;

	while (str[f] != '\0')
	{
		if (str[f] == '\n')
			break;
		f++;
	}
	str[f] = '\0';
}


void copy_string(char *source, char *wayy)
{
	int s = 0;

	for (; source[s] != '\0'; i++)
		wayy[s] = source[s];
	wayy[s] = '\0';
}


int get_string_length(char *string)
{
	int n = 0;

	if (string == NULL)
		return (n);
	for (; string[n] != '\0'; n++)
		;
	return (n);
}