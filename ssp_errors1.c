#include "ssp_shell.h"

/**
 * pr_err - prints an error message
 *
 * @err_typ: string containing specified error type
 * @inf: the parameter & return inf struct
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

void pr_err(info_t *inf, char *err_typ)
{
	_eputs(inf->fname);
	_eputs(": ");
	pr_num_bs(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(err_typ);
}

/**
 * rpl_comm - function replaces first instance of '#' with '\0'
 *
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */

void rpl_comm(char *buf)
{
	int w;

	for (w = 0; buf[w] != '\0'; w++)
		if (buf[w] == '#' && (!w || buf[w - 1] == ' '))
		{
			buf[w] = '\0';
			break;
		}
}

/**
 * pr_num_bs - function prints a decimal (integer) number (bs 10)
 *
 * @fd: the filedescriptor to write to
 * @inp: the input
 *
 * Return: number of characters printed
 */

int pr_num_bs(int inp, int fd)
{
	unsigned int rel;
	unsigned int ent;
	int w;
	int cnt = 0;
	int (*__putchar)(char) = _putchar;

	if (fd == STDERR_FILENO)
		__putchar = _outp_stderr;
	if (inp < 0)
	{
		rel = -inp;
		__putchar('-');
		cnt++;
	}
	else
		rel = inp;
	ent = rel;
	for (w = 1000000000; w > 1; w /= 10)
	{
		if (rel / w)
		{
			__putchar('0' + ent / w);
			cnt++;
		}
		ent %= w;
	}
	__putchar('0' + ent);
	cnt++;

	return (cnt);
}

/**
 * str_int - converts a string to an integer
 *
 * @a_z: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int str_int(char *a_z)
{
	int w = 0;
	unsigned long int result = 0;

	if (*a_z == '+')
		a_z++;
	for (w = 0; a_z[w] != '\0'; w++)
	{
		if (a_z[w] >= '0' && a_z[w] <= '9')
		{
			result *= 10;
			result += (a_z[w] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _conv_ - converter function, a clone of itoa
 *
 * @bs: bs
 * @arg_f: argument arg_flags
 * @num: number
 *
 * Return: string
 */

char *_conv_(long int num, int bs, int arg_f)
{
	unsigned long i = num;
	char s = 0;
	static char buff[50];
	char *pointer;
	static char *str_char;

	if (!(arg_f & CONVERT_UNSIGNED) && num < 0)
	{
		i = -num;
		s = '-';
	}
	str_char = arg_f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buff[49];
	*pointer = '\0';

	do
	{
		*--pointer = str_char[i % bs];
		i /= bs;
	} while (i != 0);

	if (s)
		*--pointer = s;
	return (pointer);
}
