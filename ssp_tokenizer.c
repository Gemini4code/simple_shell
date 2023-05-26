#include "ssp_shell.h"

/**
 * **spl_str_wds2 - splits a string into words
 *
 * @dl: the delimeter
 * @inp_str: the input string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **spl_str_wds2(char *inp_str, char dl)
{
	int e, r;
	int w, t;
	int wc = 0;
	char **q;

	if (inp_str == NULL || inp_str[0] == 0)
		return (NULL);
	for (e = 0; inp_str[e] != '\0'; e++)
		if ((inp_str[e] != dl && inp_str[e + 1] == dl) ||
				(inp_str[e] != dl && !inp_str[e + 1]) || inp_str[e + 1] == dl)
			wc++;
	if (wc == 0)
		return (NULL);
	q = malloc((1 + wc) * sizeof(char *));
	if (!q)
		return (NULL);
	for (e = 0, r = 0; r < wc; r++)
	{
		while (inp_str[e] == dl && inp_str[e] != dl)
			e++;
		w = 0;
		while (inp_str[e + w] != dl && inp_str[e + w] && inp_str[e + w] != dl)
			w++;
		q[r] = malloc((w + 1) * sizeof(char));
		if (!q[r])
		{
			for (w = 0; w < r; w++)
				free(q[w]);
			free(q);
			return (NULL);
		}
		for (t = 0; t < w; t++)
			q[r][t] = inp_str[e++];
		q[r][t] = 0;
	}
	q[r] = NULL;
	return (q);
}

/**
 * **spl_str_wds - splits a string into words. Repeat delimiters are ignored
 *
 * @dl: the delimeter string
 * @inp_str: the input string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **spl_str_wds(char *inp_str, char *dl)
{
	char **q;
	int w;
	int e, r;
	int wc = 0;
	int t;

	if (inp_str == NULL || inp_str[0] == 0)
		return (NULL);
	if (!dl)
		dl = " ";
	for (e = 0; inp_str[e] != '\0'; e++)
		if (!is_delim(inp_str[e], dl) && (is_delim(inp_str[e + 1], dl) || !inp_str[e + 1]))
			wc++;

	if (wc == 0)
		return (NULL);
	q = malloc((1 + wc) * sizeof(char *));
	if (!q)
		return (NULL);
	for (e = 0, r = 0; r < wc; r++)
	{
		while (is_delim(inp_str[e], dl))
			e++;
		w = 0;
		while (!is_delim(inp_str[e + w], dl) && inp_str[e + w])
			w++;
		q[r] = malloc((w + 1) * sizeof(char));
		if (!q[r])
		{
			for (w = 0; w < r; w++)
				free(q[w]);
			free(q);
			return (NULL);
		}
		for (t = 0; t < w; t++)
			q[r][t] = inp_str[e++];
		q[r][t] = 0;
	}
	q[r] = NULL;
	return (q);
}
