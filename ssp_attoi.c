#include "ssp_shell.h"

/**
 *_atoi - converts string to integer
 *@s: string to be converted
 *Return: 0 means no numbers in string, otherwise new number
 */

int _atoi(char *s)
{
	int op;
	unsigned int res = 0;
	int x;
	int sn = 1;
	int nb = 0;

	for (x = 0; s[x] != '\0' && nb != 2; x++)
	{
		if (s[x] == '-')
			sn *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			nb = 1;
			res *= 10;
			res += (s[x] - '0');
		}
		else if (nb == 1)
			nb = 2;
	}

	if (sn == -1)
		op = -res;
	else
		op = res;

	return (op);
}

/**
 * inter_a - returns true for interactive mode shell.
 * @inf: structure address
 * Return: inter_a mode for 1, otherwise 0
 */

int inter_a(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 *alpha - checks for alphabetic character
 *@z: The character to input
 *Return: 1 means @z is alphabetic, 0 means otherwise
 */

int alpha(int z)
{
	if ((z >= 'a' && z <= 'z') || (z >= 'A' && z <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * del - checks if character is a delimiter
 * @a: the character to check
 * @de_l: the delimiter string
 * Return: 1 means true, 0 means false
 */

int del(char a, char *de_l)
{
	while (*de_l)
		if (*de_l++ == a)
			return (1);
	return (0);
}
