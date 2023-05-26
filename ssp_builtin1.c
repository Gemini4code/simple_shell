#include "ssp_shell.h"

/**
 * set_alias - sets alias to string
 * @inf: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *inf, char *str)
{
	char *u;

	u = _strchr(str, '=');
	if (!u)
		return (1);
	if (!*++u)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * history - displays records history records, one command per line, preceded
 *              by line numbers, beginning from 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0
 */

int history(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * alias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int alias(info_t *inf)
{
	list_t *junc = NULL;
	int r = 0;
	char *u = NULL;

	if (inf->argc == 1)
	{
		junc = inf->alias;
		while (junc)
		{
			print_alias(junc);
			junc = junc->next;
		}
		return (0);
	}
	for (r = 1; inf->argv[r]; r++)
	{
		u = _strchr(inf->argv[r], '=');
		if (u)
			set_alias(inf, inf->argv[r]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[r], '='));
	}

	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *inf, char *str)
{
	char c;
	char *u;
	int ret;

	u = _strchr(str, '=');
	if (!u)
		return (1);
	c = *u;
	*u = 0;
	ret = delete_node_at_index(&(inf->alias),
														 get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*u = c;
	return (ret);
}

/**
 * print_alias - prints an alias string
 * @junc: the alias junction or node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *junc)
{
	char *u = NULL;
	char *s = NULL;

	if (junc)
	{
		u = _strchr(junc->str, '=');
		for (s = junc->str; s <= u; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(u + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
