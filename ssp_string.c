#include "ssp_shell.h"

/**
 * ccat_str - concatenates two strings
 *
 * @buf_src: the source buffer
 * @buf_d: the destination buffer
 *
 * Return: pointer to destination buffer
 */

char *cat_str(char *buf_d, char *buf_src)
{
	char *ret = buf_d;

	while (*buf_d)
		buf_d++;
	while (*buf_src)
		*buf_d++ = *buf_src++;
	*buf_d = *buf_src;
	return (ret);
}

/**
 * lex_str - performs lexicogarphic comparison of two strings.
 *
 * @or_i: the first string
 * @od_ii: the second stiang
 *
 * Return: negative if or_i < od_ii, positive if or_i > od_ii, zero if or_i == od_ii
 */
int lex_str(char *or_i, char *od_ii)
{
	while (*or_i && *od_ii)
	{
		if (*or_i != *od_ii)
			return (*or_i - *od_ii);
		or_i++;
		od_ii++;
	}
	if (*or_i == *od_ii)
		return (0);
	else
		return (*or_i < *od_ii ? -1 : 1);
}

/**
 * beg_hr - checks if needle starts with haystack
 *
 * @s_ndl: the substring to find
 * @h_s: string to search
 *
 * Return: address of next char of h_s or NULL
 */

char *beg_hr(const char *h_s, const char *s_ndl)
{
	while (*s_ndl)
		if (*s_ndl++ != *h_s++)
			return (NULL);
	return ((char *)h_s);
}

/**
 * len_str - returns the length of a string
 *
 * @ck_s: the string whose length to check
 *
 * Return: integer length of string
 */

int len_str(char *ck_s)
{
	int t = 0;

	if (!ck_s)
		return (0);

	while (*ck_s++)
		t++;
	return (t);
}
