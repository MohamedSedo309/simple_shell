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

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps the
 *command name into its right function 
 *@command_name: command name
 *@func: the function that executes the command
 */

typedef struct map
{
char *command_name;
void (*func)(char **command);
} map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*helpers1.c*/
void print(char *, int);
char **tokin_maker(char *, char *);
void remove_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*helpers2.c*/
int _strcomp(char *, char *);
char *_strconnect(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strsearch(char *, char);

/*helpers3.c*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *p, unsigned int old, unsigned int new_s);
void ctrl_c_handler(int);
void remove_comment(char *);

/*utils.c*/
int parse_cmd(char *);
void execute_cmd(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);

/*built_in_functions.c*/
void env(char **);
void quit(char **);

/*main functions*/
extern void non_interactive(void);
extern void initializer(char **current_command, int type_command);

#endif
