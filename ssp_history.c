#include "ssp_shell.h"

/**
 * _mkhist - creates a file, or appends to an existing file
 *
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int _mkhist(info_t *inf)
{
	char *fs_id = get_hist_fs(inf);
	list_t *junc = NULL;
	ssize_t fd;

	if (!fs_id)
		return (-1);

	fd = open(fs_id, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fs_id);
	if (fd == -1)
		return (-1);
	for (junc = inf->history; junc; junc = junc->next)
	{
		_putsfd(junc->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _re_numhist - renumbers the history linked list after changes
 *
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int _re_numhist(info_t *inf)
{
	list_t *junc = inf->history;
	int m = 0;

	while (junc)
	{
		junc->num = m++;
		junc = junc->next;
	}
	return (inf->histcount = m);
}

/**
 * get_hist_fs - gets the history file
 *
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_fs(info_t *inf)
{
	char *foldr;
	char *bu;

	foldr = _getenv(inf, "HOME=");
	if (!foldr)
		return (NULL);
	bu = malloc(sizeof(char) * (_strlen(foldr) + _strlen(HIST_FILE) + 2));
	if (!bu)
		return (NULL);
	bu[0] = 0;
	_strcpy(bu, foldr);
	_strcat(bu, "/");
	_strcat(bu, HIST_FILE);
	return (bu);
}

/**
 * ct_hist - reads history from file
 *
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int ct_hist(info_t *inf)
{
	int fl = 0;
	ssize_t fd;
	int _ln_ct = 0;
	ssize_t f_sz = 0;
	int m;
	char *fs_id = get_hist_fs(inf);
	ssize_t rd_len;
	struct stat ch;
	char *bu = NULL;

	if (!fs_id)
		return (0);

	fd = open(fs_id, O_RDONLY);
	free(fs_id);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &ch))
		f_sz = ch.st_size;
	if (f_sz < 2)
		return (0);
	bu = malloc(sizeof(char) * (f_sz + 1));
	if (!bu)
		return (0);
	rd_len = read(fd, bu, f_sz);
	bu[f_sz] = 0;
	if (rd_len <= 0)
		return (free(bu), 0);
	close(fd);
	for (m = 0; m < f_sz; m++)
		if (bu[m] == '\n')
		{
			bu[m] = 0;
			app_hist_ls(inf, bu + fl, _ln_ct++);
			fl = m + 1;
		}
	if (fl != m)
		app_hist_ls(inf, bu + fl, _ln_ct++);
	free(bu);
	inf->histcount = _ln_ct;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	_re_numhist(inf);
	return (inf->histcount);
}

/**
 * app_hist_ls - adds entry to a history linked list
 *
 * @bu: buffer
 * @_ln_ct: the history _ln_ct, histcount
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: Always 0
 */

int app_hist_ls(info_t *inf, char *bu, int _ln_ct)
{
	list_t *junc = NULL;

	if (inf->history)
		junc = inf->history;
	add_node_end(&junc, bu, _ln_ct);

	if (!inf->history)
		inf->history = junc;
	return (0);
}
