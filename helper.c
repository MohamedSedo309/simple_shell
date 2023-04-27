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
noww = reallocate_memory(noww, sizeof(*noww) * num_done,
			 sizeof(*noww) * (num_done + 1));
noww[num_done] = tk;
tk = tokenize_string_r(NULL, done, &pointer_s);
num_done++;
}
noww = reallocate_memory(noww, sizeof(*noww) * num_done,
			 sizeof(*noww) * (num_done + 1));
noww[num_done] = NULL;
return (noww);
}


void remove_newline_character(char *str)
{
int i = 0;
while (str[i] != '\0')
{
if (str[i] == '\n')
{
break;
}
i++;
}
str[i] = '\0';
}

void print_message(char *string, int stream)
{
int i = 0;
for (i = 0; string[i] != '\0'; i++)
{
write(stream, &string[i], 1);
}
}



void copy_string(char *src, char *dest)
{
int i = 0;
for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
}




int get_string_length(char *str)
{
int len = 0;
if (str == NULL)
{
return (len);
}
for (len = 0; str[len] != '\0'; len++)
{
}
return (len);
}
