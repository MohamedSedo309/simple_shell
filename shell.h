#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

export PATH=$PATH:/bin

extern char **environ;


/**
 * struct singlelist - singly linked list
 * @num: int field
 * @str: a string
 * @next: pointer to the next node
 */
typedef struct singlelist
{
	int num;
	char *str;
	struct singlelist *next;
} list_s;

/**
 *@arg: argg
 *@argv:arg vector
 *@path: a string path
 *@argc: args count
 *@count_line: the error counter
 *@err_number: the error code for exits
 *@conutline_flag: conutline_flag
 *@filename: filename
 *@env: local copy of environ
 *@environ: copy of environ from env
 *@history: history node
 *@alias: alias node
 *@env_changed: if environ was changed
 *@status: the return status
 *@cmd_buffer: address of pointer
 *@cmd_buffer_type: cmmd type
 *@readfile: read line
 *@histcounter: the history line number counter
 */
typedef struct passinfoormation
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int err_number;
	int conutline_flag;
	char *filename;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buffer_type; /* CMD_type ||, &&, ; */
	int readfile;
	int histcounter;
} infooo;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 *struct builtins - contains a builtins string and related function
 *@type: the builtins command flag
 *@func: the function
 */
typedef struct builtins
{
	char *type;
	int (*func)(infooo *);
} builtin_vars;


int hsh(infooo *, char **);
int get_builtin(infooo *);
void find_cmmd(infooo *);
void fork_cmmd(infooo *);

int is_a_cmd(infooo *, char *);
char *duplicate_char(char *, int, int);
char *get_path(infooo *, char *, char *);

void print_message_error(char *);
int print_char(char);
int echo_fd(char c, int fd);
int echo_string_fd(char *str, int fd);

int get_string_length(char *);
int compare_strings(char *, char *);
char *begain_with(const char *, const char *);
char *concatenate_strings(char *, char *);

char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int _putchar(char);

char *copy_string2(char *, char *, int);
char *concatenate_strings2(char *, char *, int);
char *find_char(char *, char);

char **tokinize_string(char *, char *);
char **tokinize_string2(char *, char);


char *set_memory(char *, char, unsigned int);
void ffree_memory(char **);
void *_realloc_mem(void *, unsigned int, unsigned int);

int free_buff(void **);

int is_interactive(infooo *);
int is_delimeter(char, char *);
int isalphabet(int);
int convert_str_to_int(char *);

int err_convert_str_to_int(char *);
void print_e_message(infooo *, char *);
int print_dec(int, int);
char *conv_num(long int, int, int);
void remove_comment(char *);

int exit_shell(infooo *);
int change_dirr(infooo *);
int helper(infooo *);

int get_historyyyy(infooo *);
int get_myalias(infooo *);

ssize_t input_getter(infooo *);
int line_getter(infooo *, char **, size_t *);
void ctrl_c_handler(int);

void delete_info(infooo *);
void put_info(infooo *, char **);
void delete_info_all(infooo *, int);

char *get_enviroment(infooo *, const char *);
int current_env(infooo *);
int init_env(infooo *);
int remove_env(infooo *);
int make_env_list(infooo *);

char **copy_env_string(infooo *);
int remove_env_var(infooo *, char *);
int make_env(infooo *, char *, char *);

char *get_ffhistory(infooo *info);
int print_hiss(infooo *info);
int get_history_str(infooo *info);
int hiss_list_builder(infooo *info, char *buf, int linecount);
int include_hist(infooo *info);

list_s *create_node(list_s **, const char *, int);
list_s *create_end_node(list_s **, const char *, int);
size_t print_str_part(const list_s *);
int delete_atindex(list_s **, unsigned int);
void freemem_list(list_s **);

size_t getLength(const list_s *);
char **get_list_str_part(list_s *);
size_t print_list_s(const list_s *);
list_s *get_node_starter(list_s *, char *, char);
ssize_t get_node_arrange(list_s *, list_s *);

int is_a_chain(infooo *, char *, size_t *);
void check_if_chain(infooo *, char *, size_t *, size_t, size_t);
int aliasreplace(infooo *);
int var_replace(infooo *);
int replace_strrr(char **, char *);

#endif /*SHELL.H*/
