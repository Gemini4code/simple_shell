#include "ssp_shell.h"

/**
 * str_rplc - replaces string
 *
 * @nw_str: nw_str string
 * @addr_old: address of addr_old string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int str_rplc(char *nw_str, char **addr_old)
{
	free(*addr_old);
	*addr_old = nw_str;
	return (1);
}

/**
 * ch_ls_chain - checks we should continue chaining based on last status
 *
 * @buf: the char buffer
 * @addr_pr: address of current position in buf
 * @buff_len: length of buf
 * @inf: the parameter struct
 * @j: starting position in buf
 *
 * Return: Void
 */

void ch_ls_chain(size_t *addr_pr, size_t j, info_t *inf, char *buf, size_t buff_len)
{
	size_t x = *addr_pr;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[j] = 0;
			x = buff_len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[j] = 0;
			x = buff_len;
		}
	}

	*addr_pr = x;
}

/**
 * alias_rplc - replaces an aliases in the tokenized string
 *
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int alias_rplc(info_t *inf)
{
	list_t *blk;
	char *addr_pr;
	int j;

	for (j = 0; j < 10; j++)
	{
		blk = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!blk)
			return (0);
		free(inf->argv[0]);
		addr_pr = _strchr(blk->str, '=');
		if (!addr_pr)
			return (0);
		addr_pr = _strdup(addr_pr + 1);
		if (!addr_pr)
			return (0);
		inf->argv[0] = addr_pr;
	}
	return (1);
}

/**
 * ch_chain_del - test if current char in buffer is a chain delimeter
 *
 * @buf: the char buffer
 * @addr_pr: address of current position in buf
 * @inf: the parameter struct
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int ch_chain_del(char *buf, info_t *inf, size_t *addr_pr)
{
	size_t x = *addr_pr;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';') /* found end of this command */
	{
		buf[x] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*addr_pr = x;
	return (1);
}

/**
 * vars_rplc - replaces vars in the tokenized string
 *
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int vars_rplc(info_t *inf)
{
	list_t *blk;
	int j = 0;

	for (j = 0; inf->argv[j]; j++)
	{
		if (inf->argv[j][0] != '$' || !inf->argv[j][1])
			continue;

		if (!_strcmp(inf->argv[j], "$?"))
		{
			str_rplc(&(inf->argv[j]),
							 _strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[j], "$$"))
		{
			str_rplc(&(inf->argv[j]),
							 _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		blk = node_starts_with(inf->env, &inf->argv[j][1], '=');
		if (blk)
		{
			str_rplc(&(inf->argv[j]),
							 _strdup(_strchr(blk->str, '=') + 1));
			continue;
		}
		str_rplc(&inf->argv[j], _strdup(""));
	}
	return (0);
}
