#include "ssp_shell.h"

/**
 * cd - changes current working directory
 *
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *  Return: 0 only
 */

int cd(info_t *inf)
{
	char *dr;
	char *e;
	int cd_ret;
	char bu[1024];

	e = getcwd(bu, 1024);
	if (!e)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!inf->argv[1])
	{
		dr = _getenv(inf, "HOME=");
		if (!dr)
			cd_ret = /* TODO: what should this be? */
					chdir((dr = _getenv(inf, "PWD=")) ? dr : "/");
		else
			cd_ret = chdir(dr);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(e);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		cd_ret = /* TODO: what should this be? */
				chdir((dr = _getenv(inf, "OLDPWD=")) ? dr : "/");
	}
	else
		cd_ret = chdir(inf->argv[1]);
	if (cd_ret == -1)
	{
		print_error(inf, "no such file or directory");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(bu, 1024));
	}
	return (0);
}

/**
 * help - changes the current directory of the process
 *
 *  Return: 0
 */

int help(info_t *inf)
{
	char **func_arg;

	func_arg = inf->argv;
	_puts("help successful! Function doesn't exist\n");
	if (0)
		_puts(*func_arg); /* temp att_unused workaround */
	return (0);
}

/**
 * exit_sh - exits the shell
 *
 *  Return: 0 as exit status
 */

int exit_sh(info_t *inf)
{
	int exitsh_inspect;

	if (inf->argv[1])
	{
		exitsh_inspect = _erratoi(inf->argv[1]);
		if (exitsh_inspect == -1)
		{
			inf->status = 2;
			print_error(inf, "unknown number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}
