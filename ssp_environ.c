#include "ssp_shell.h"

/**
 * get_env - obtains an environ variable's value
 * @lab: env var label or name
 * @inf: Contains  arguments for running function prototype.
 *
 * Return: the value
 */

char *get_env(info_t *inf, const char *lab)
{
	list_t *opt = inf->env;
	char *p;

	while (opt)
	{
		p = starts_with(opt->str, lab);
		if (p && *p)
			return (p);
		opt = opt->next;
	}
	return (NULL);
}

/**
 * set_env - starts a new environment variable,
 *             or modify an existing one
 * @inf: Contains  arguments for running function prototype.
 *
 *  Return: 0
 */

int set_env(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Insufficient arguments!\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * env - prints the current environment
 * @inf: Contains  arguments for running function prototype.
 *
 * Return: 0
 */

int env(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * pevn_list - populates env linked list
 * @inf: Contains  arguments for running function prototype. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int pevn_list(info_t *inf)
{
	size_t x;
	list_t *opt = NULL;

	for (x = 0; environ[x]; x++)
		add_node_end(&opt, environ[x], 0);
	inf->env = opt;
	return (0);
}

/**
 * unset_env - Remove an environment variable
 * @inf: Contains  arguments for running function prototype. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int unset_env(info_t *inf)
{
	int x;

	if (inf->argc == 1)
	{
		_eputs("More arguments required!\n");
		return (1);
	}
	for (x = 1; x <= inf->argc; x++)
		_unsetenv(inf, inf->argv[x]);

	return (0);
}

