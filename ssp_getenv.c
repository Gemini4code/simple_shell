#include "ssp_shell.h"

/**
 * init_env - Initialize a new environment variable,
 *             or modify an existing one
 *
 * @v: the string env v property
 * @obj: the string env v obj
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0
 */

int init_env(info_t *inf, char *v, char *obj)
{
	list_t *nd;
	char *h;
	char *bu = NULL;

	if (!v || !obj)
		return (0);

	bu = malloc(_strlen(v) + _strlen(obj) + 2);
	if (!bu)
		return (1);
	_strcpy(bu, v);
	_strcat(bu, "=");
	_strcat(bu, obj);
	nd = inf->env;
	while (nd)
	{
		h = beg_w(nd->str, v);
		if (h && *h == '=')
		{
			free(nd->str);
			nd->str = bu;
			inf->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(inf->env), bu, 0);
	free(bu);
	inf->env_changed = 1;
	return (0);
}

/**
 * cat_env - returns the string array copy of our environ
 *
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

char **cat_env(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 *
 * @v: the string env v property
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: 1 on delete, 0 otherwise
 */

int _unsetenv(info_t *inf, char *v)
{
	list_t *nd = inf->env;
	size_t i = 0;
	char *h;

	if (!nd || !v)
		return (0);

	while (nd)
	{
		h = beg_w(nd->str, v);

		if (h && *h == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), i);
			i = 0;
			nd = inf->env;
			continue;
		}
		nd = nd->next;
		i++;
	}
	return (inf->env_changed);
}
