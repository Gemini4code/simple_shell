#include "ssp_shell.h"

/**
 **chr_loc - locates a character in a string
 *
 *@f: the character to look for
 *@p: the string to be parsed
 *
 *Return: (p) a pointer to the memory area p
 */

char *chr_loc(char *p, char f)
{
	do
	{
		if (*p == f)
			return (p);
	} while (*p++ != '\0');

	return (NULL);
}

/**
 **ccat_str - concatenates two strings
 *
 *@origin: the second string
 *@x: the amount of bytes to be maximally used
 *@base: the first string
 *
 *Return: the concatenated string
 */

char *ccat_str(char *base, char *origin, int x)
{
	char *p = base;
	int d;
	int z;

	z = 0;
	d = 0;
	while (base[z] != '\0')
		z++;
	while (origin[d] != '\0' && d < x)
	{
		base[z] = origin[d];
		z++;
		d++;
	}
	if (d < x)
		base[z] = '\0';
	return (p);
}

/**
 * *cp_str - copies a string
 *
 *@base: the destination string to be copied to
 *@origin: the source string
 *@x: the amount of characters to be copied
 *
 *Return: the concatenated string
 */

char *cp_str(char *base, char *origin, int x)
{
	int d;
	char *p = base;
	int z;

	z = 0;
	while (origin[z] != '\0' && z < x - 1)
	{
		base[z] = origin[z];
		z++;
	}
	if (z < x)
	{
		d = z;
		while (d < x)
		{
			base[d] = '\0';
			d++;
		}
	}
	return (p);
}
