#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* for _conv_() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define INFO_INIT                                                           \
	{                                                                         \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
				0, 0, 0                                                             \
	}

extern char **environ;

/**
 * struct liststr - singly linked list
 * @next: points to the next node
 * @num: the number field
 * @str: a string
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/**
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@alias: the alias node
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@readfd: the fd from which to read line input
 *@argc: the argument count
 *@path: a string path for the current command
 *@histcount: the history line number count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@status: the return status of the last exec'd command
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@linecount_flag: if on count this line of input
 *@env_changed: on if environ was changed
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;		/* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

/* toem_string.c */
int len_str(char *);
int lex_str(char *, char *);
char *beg_hr(const char *, const char *);
char *cat_str(char *, char *);

/* toem_exits.c */
char *cp_str(char *, char *, int);
char *ccat_str(char *, char *, int);
char *chr_loc(char *, char);

/* toem_tokenizer.c */
char **spl_str_wds2(char *, char);
char **spl_str_wds(char *, char *);

/* toem_string1.c */
char *_cp_str(char *, char *);
char *_d_str(const char *);
void inp_pr(char *);
int stdo_w(char);

/* toem_realloc.c */
char *fill_mem(char, unsigned int, char *);
void str_fr(char **);
void *bk_reall(unsigned int, void *, unsigned int);

/* toem_memory.c */
int ptr_null(void **);

/* toem_atoi.c */
int inter_a(info_t *);
int del(char, char *);
int alpha(int);
int _atoi(char *);

/* toem_lists1.c */
size_t len_lklist(const list_t *);
char **ls_str(list_t *);
size_t pr_ls_t(const list_t *);
list_t *rtn_blk_pref(list_t *, char *, char);
ssize_t get_blk_index(list_t *, list_t *);

/* toem_vars.c */
int ch_chain_del(char *, info_t *, size_t *);
void ch_ls_chain(size_t *, size_t, info_t *, char *, size_t);
int alias_rplc(info_t *);
int vars_rplc(info_t *);
int str_rplc(char *, char **);

/* toem_errors1.c */
int str_int(char *);
void pr_err(info_t *, char *);
int pr_num_bs(int, int);
char *_conv_(long int, int, int);
void rpl_comm(char *);

/* toem_builtin.c */
int exit_sh(info_t *);
int cd(info_t *);
int help(info_t *);

/* toem_builtin1.c */
int history(info_t *);
int set_alias(info_t *, char *);
int alias(info_t *);
int unset_alias(info_t *, char *);
int print_alias(list_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
ssize_t r_bu(info_t *, char *, size_t *);
ssize_t input_buf(info_t *, char **, size_t *);
int get_nxt_ln(info_t *, char **, size_t *);
void bl_cp(int);

/* toem_getinfo.c */
void init_str(info_t *);
void set_str(info_t *, char **);
void lib_str(info_t *, int);

/* toem_environ.c */
char *get_env(info_t *, const char *);
int env(info_t *);
int set_env(info_t *);
int unset_env(info_t *);
int penv_list(info_t *);

/* toem_getenv.c */
char **cat_env(info_t *);
int _unsetenv(info_t *, char *);
int init_env(info_t *, char *, char *);

/* toem_history.c */
char *get_hist_fs(info_t *info);
int _mkhist(info_t *info);
int ct_hist(info_t *info);
int app_hist_ls(info_t *info, char *buf, int linecount);
int _re_numhist(info_t *info);

/* toem_shloop.c */
int sh_lp(char **, info_t *);
int search_bltn(info_t *);
void p_comm_fd(info_t *);
void et_fk(info_t *);

/* toem_errors.c */
void pr_str(char *);
int _outp_stderr(char);
int outp_fd(char a_z, int fd);
int pr_inpt_str(char *str, int fd);

/* toem_lists.c */
list_t *add_bl(list_t **, const char *, int);
list_t *add_bl_end(list_t **, const char *, int);
size_t pri_str_only(const list_t *);
int rm_bl_spec(list_t **, unsigned int);
void avail_bl(list_t **);

/* toem_parser.c */
int det_exe(char *, info_t *);
char *dbl_ch(int, char *, int);
char *path_finder(char *, info_t *, char *);

/* loophsh.c */
int loophsh(char **);

#endif
