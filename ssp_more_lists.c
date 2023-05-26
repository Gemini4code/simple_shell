#include "ssp_shell.h"

/**
 * ls_str - returns an array of strings of the list->str
 *
 * @tp: pointer to first blk
 *
 * Return: array of strings
 */

char **ls_str(list_t *tp)
{
	size_t y = len_lklist(tp);
	size_t k;
	char **strs;
	char *str;
	list_t *blk = tp;

	if (!tp || !y)
		return (NULL);
	strs = malloc(sizeof(char *) * (y + 1));
	if (!strs)
		return (NULL);
	for (y = 0; blk; blk = blk->next, y++)
	{
		str = malloc(_strlen(blk->str) + 1);
		if (!str)
		{
			for (k = 0; k < y; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, blk->str);
		strs[y] = str;
	}
	strs[y] = NULL;
	return (strs);
}

/**
 * get_blk_index - gets the index of a node
 *
 * @blk: pointer to the blk
 * @tp: pointer to list tp
 *
 * Return: index of blk or -1
 */

ssize_t get_blk_index(list_t *tp, list_t *blk)
{
	size_t y = 0;

	while (tp)
	{
		if (tp == blk)
			return (y);
		tp = tp->next;
		y++;
	}
	return (-1);
}

/**
 * pr_ls_t - prints all elements of a list_t linked list
 *
 * @v: pointer to first blk
 *
 * Return: size of list
 */

size_t pr_ls_t(const list_t *v)
{
	size_t y = 0;

	while (v)
	{
		_puts(convert_number(v->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(v->str ? v->str : "(nil)");
		_puts("\n");
		v = v->next;
		y++;
	}
	return (y);
}

/**
 * len_lklist - determines length of linked list
 *
 * @v: pointer to first blk
 *
 * Return: size of list
 */

size_t len_lklist(const list_t *v)
{
	size_t y = 0;

	while (v)
	{
		v = v->next;
		y++;
	}
	return (y);
}

/**
 * rtn_blk_pref - returns nodes whose string starts with prefix
 *
 * @prefix: string to match
 * @blk: pointer to list tp
 * @c: the next character after prefix to match
 *
 * Return: match blk or null
 */

list_t *rtn_blk_pref(list_t *blk, char *prefix, char c)
{
	char *r = NULL;

	while (blk)
	{
		r = starts_with(blk->str, prefix);
		if (r && ((c == -1) || (*r == c)))
			return (blk);
		blk = blk->next;
	}
	return (NULL);
}
