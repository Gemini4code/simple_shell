#include "ssp_shell.h"

/**
 * path_finder - finds this cmd in the PATH string
 *
 * @cmd: the cmd to find
 * @str_pth: the PATH string
 * @inf: the inf struct
 *
 * Return: full _fs_pth of cmd if found or NULL
 */

char *path_finder(char *str_pth, info_t *inf, char *cmd)
{
	int curr_pos = 0;
	char *_fs_pth;
	int i = 0;

	if (!str_pth)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (det_exe(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_pth[i] || str_pth[i] == ':')
		{
			_fs_pth = dbl_ch(str_pth, curr_pos, i);
			if (!*_fs_pth)
				_strcat(_fs_pth, cmd);
			else
			{
				_strcat(_fs_pth, "/");
				_strcat(_fs_pth, cmd);
			}
			if (det_exe(inf, _fs_pth))
				return (_fs_pth);
			if (!str_pth[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * det_exe - determines if a file is an executable command
 *
 * @_fs_pth: filepath
 * @inf: the information structure
 *
 * Return: 1 means true, 0 means otherwise
 */

int det_exe(char *_fs_pth, info_t *inf)
{
	struct stat ch;

	(void)inf;
	if (!_fs_pth || stat(_fs_pth, &ch))
		return (0);

	if (ch.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dbl_ch - duplicates characters
 *
 * @start: starting index
 * @stop: stopping index
 * @str_pth: the PATH string
 *
 * Return: pointer to new buffer
 */

char *dbl_ch(int start, char *str_pth, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str_pth[i] != ':')
			buf[k++] = str_pth[i];
	buf[k] = 0;
	return (buf);
}
