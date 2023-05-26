#include "ssp_shell.h"

/**
 * lib_str - frees info_t struct fields
 * @all: true if freeing all fields
 * @inf: struct address
 */

void lib_str(info_t *inf, int all)
{
	inf->path = NULL;
	ffree(inf->argv);
	inf->argv = NULL;

	if (all)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
		inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * init_str - initializes info_t struct
 * @inf: struct address
 */

void init_str(info_t *inf)
{
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
	inf->arg = NULL;
}

/**
 * set_str - initializes info_t struct
 * @av: argument vector
 * @inf: struct address
 */

void set_str(info_t *inf, char **av)
{
	int l = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (l = 0; inf->argv && inf->argv[l]; l++)
			;
		inf->argc = l;

		replace_alias(inf);
		replace_vars(inf);
	}
}
