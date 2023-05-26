#include "ssp_shell.h"

/**
 * stdo_w - writes the character chr to stdout
 *
 * @chr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int stdo_w(char chr)
{
	static char bu[WRITE_BUF_SIZE];
	static int e;

	if (chr == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, bu, e);
		e = 0;
	}
	if (chr != BUF_FLUSH)
		bu[e++] = chr;
	return (1);
}

/**
 * _d_str - duplicates a string
 *
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_d_str(const char *str)
{
	char *loc;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	loc = malloc(sizeof(char) * (len + 1));
	if (!loc)
		return (NULL);
	for (len++; len--;)
		loc[len] = *--str;
	return (loc);
}

/**
 *inp_pr - prints an input string
 *
 *@str: the string to be printed
 *
 * Return: Nothing
 */

void inp_pr(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		stdo_w(str[e]);
		e++;
	}
}

/**
 * _cp_str - copies a string
 *
 * @org: the source
 * @lat: the destination
 *
 * Return: pointer to destination
 */

char *_cp_str(char *org, char *lat)
{
	int e = 0;

	if (lat == org || org == 0)
		return (lat);
	while (org[e])
	{
		lat[e] = org[e];
		e++;
	}
	lat[e] = 0;
	return (lat);
}
