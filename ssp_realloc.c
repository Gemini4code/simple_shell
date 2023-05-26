#include "ssp_shell.h"

/**
 * bl_reall - reallocates a block of memory
 *
 * @bk_pre: byte size of previous block
 * @bk_nw: byte size of new block
 * @pre_mall_ptr: pointer to previous malloc'ated block
 *
 * Return: pointer to da ol'block nameen.
 */

void *bk_reall(unsigned int bk_pre, void *pre_mall_ptr, unsigned int bk_nw)
{
	char *d;

	if (!pre_mall_ptr)
		return (malloc(bk_nw));
	if (!bk_nw)
		return (free(pre_mall_ptr), NULL);
	if (bk_nw == bk_pre)
		return (pre_mall_ptr);

	d = malloc(bk_nw);
	if (!d)
		return (NULL);

	bk_pre = bk_pre < bk_nw ? bk_pre : bk_nw;
	while (bk_pre--)
		d[bk_pre] = ((char *)pre_mall_ptr)[bk_pre];
	free(pre_mall_ptr);
	return (d);
}

/**
 **_fill_mem - fills memory with a constant byte
 *
 *@bt_pt: the byte to fill *mem_ptr with
 *@f_amt: the amount of bytes to be filled
 *@mem_ptr: the pointer to the memory area
 *
 *Return: (mem_ptr) a pointer to the memory area mem_ptr
 */

char *fill_mem(char bt_pt, unsigned int f_amt, char *mem_ptr)
{
	unsigned int g;

	for (g = 0; g < f_amt; g++)
		mem_ptr[g] = bt_pt;
	return (mem_ptr);
}

/**
 * str_fr - frees a string of strings
 *
 * @ss: string of strings
 */

void str_fr(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}
