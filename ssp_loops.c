#include "ssp_shell.h"

/**
 * et_fk - forks a an exec thread to run cmd
 *
 * @inf: the parameter & return inf struct
 *
 * Return: void
 */

void et_fk(info_t *inf)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

/**
 * search_bltn - finds a builtin command
 *
 * @inf: the parameter & return inf struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */

int search_bltn(info_t *inf)
{
	int b_r = -1;
	builtin_table b_in_t[] = {
			{"exit", exit_sh},
			{"env", env},
			{"help", help},
			{"history", history},
			{"setenv", _unsetenv},
			{"unsetenv", unset_env},
			{"cd", cd},
			{"alias", alias},
			{NULL, NULL}};
	int m;

	for (m = 0; b_in_t[m].type; m++)
		if (_strcmp(inf->argv[0], b_in_t[m].type) == 0)
		{
			inf->line_count++;
			b_r = b_in_t[m].func(inf);
			break;
		}
	return (b_r);
}

/**
 * sh_lp - main shell loop
 *
 * @m_argv: the argument vector from main()
 * @inf: the parameter & return inf struct
 *
 * Return: 0 for success, 1 for error
 */

int sh_lp(char **m_argv, info_t *inf)
{
	int r_bltn = 0;
	ssize_t h = 0;

	while (h != -1 && r_bltn != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		h = get_input(inf);
		if (h != -1)
		{
			set_info(inf, m_argv);
			r_bltn = search_bltn(inf);
			if (r_bltn == -1)
				p_comm_fd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (r_bltn == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (r_bltn);
}

/**
 * p_comm_fd - finds a command in PATH
 *
 * @inf: the parameter & return inf struct
 *
 * Return: void
 */

void p_comm_fd(info_t *inf)
{
	int m;
	int y;
	char *path = NULL;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (m = 0, y = 0; inf->arg[m]; m++)
		if (!is_delim(inf->arg[m], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		et_fk(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=") || inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			et_fk(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}
