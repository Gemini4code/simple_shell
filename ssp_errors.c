#include "ssp_shell.h"

/**
 * pr_inpt_str - prints an input string
 *
 * @fd: the filedescriptor to write to
 * @str: the string to be printed
 *
 * Return: the number of chars put
 */

int pr_inpt_str(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += outp_fd(*str++, fd);
	}
	return (n);
}

/**
 * outp_fd - writes the character a_z to given fd
 *
 * @fd: The filedescriptor to write to
 * @a_z: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int outp_fd(char a_z, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (a_z == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (a_z != BUF_FLUSH)
		buf[n++] = a_z;
	return (1);
}

/**
 * _outp_stderr - writes the character a_z to stderr
 *
 * @a_z: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _outp_stderr(char a_z)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (a_z == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (a_z != BUF_FLUSH)
		buf[n++] = a_z;
	return (1);
}

/**
 * pr_str - prints out input string
 *
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void pr_str(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_outp_stderr(str[n]);
		n++;
	}
}
