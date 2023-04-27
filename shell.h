#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define new_min(x, y) (((x) < (y)) ? (x) : (y))
typedef struct cmd_map
{
char *cmd_name;
void (*func)(char **command);
} cmd_map_t;

extern char **environment;
extern char *input_line;
extern char **input_commands;
extern char *shell_name;
extern int status;

void print_message(char *, int);
char **tokenize_string(char *, char *);
void remove_newline_character(char *);
int get_string_length(char *);
void copy_string(char *, char *);

int compare_strings(char *, char *);
char *concatenate_strings(char *, char *);
int get_prefix_length(char *, char *);
int get_not_matching_prefix_length(char *, char *);
char *find_char(char *, char);


char *tokenize_string_r(char *, char *, char **);
int convert_string_to_integer(char *);
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_signal_handler(int);
void remove_comments(char *);


int parse_input_command(char *);
void execute_input_command(char **, int);
char *find_command_in_path(char *);
void (*get_command_function(char *))(char **);
char *get_environment_variable(char *);


void show_environment_variables(char **);
void exit_shell(char **);


extern void run_shell_interactively(void);
extern void initialize_shell(char **current_command, int cmd_type);

#endif /*SHELL_H*/
