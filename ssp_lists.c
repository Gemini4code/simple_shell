#include "ssp_shell.h"

/**
 * add_bl_end - adds a bl to the end of the list
 *
 * @str: str field of bl
 * @num: bl index used by history
 * @ldr: address of pointer to ldr bl
 *
 * Return: size of list
 */

list_t *add_bl_end(list_t **ldr, const char *str, int num)
{
	list_t *bl;
	list_t *new_bl;

	if (!ldr)
		return (NULL);

	bl = *ldr;
	new_bl = malloc(sizeof(list_t));
	if (!new_bl)
		return (NULL);
	_memset((void *)new_bl, 0, sizeof(list_t));
	new_bl->num = num;
	if (str)
	{
		new_bl->str = _strdup(str);
		if (!new_bl->str)
		{
			free(new_bl);
			return (NULL);
		}
	}
	if (bl)
	{
		while (bl->next)
			bl = bl->next;
		bl->next = new_bl;
	}
	else
		*ldr = new_bl;
	return (new_bl);
}

/**
 * avail_bl - frees all nodes of a list
 *
 * @head_ptr: address of pointer to ldr bl
 *
 * Return: void
 */

void avail_bl(list_t **head_ptr)
{
	list_t *bl, *next_node, *ldr;

	if (!head_ptr || !*head_ptr)
		return;
	ldr = *head_ptr;
	bl = ldr;
	while (bl)
	{
		next_node = bl->next;
		free(bl->str);
		free(bl);
		bl = next_node;
	}
	*head_ptr = NULL;
}

/**
 * pri_str_only - prints only the str element of a list_t linked list
 *
 * @v: pointer to first bl
 *
 * Return: size of list
 */

size_t pri_str_only(const list_t *v)
{
	size_t o = 0;

	while (v)
	{
		_puts(v->str ? v->str : "(nil)");
		_puts("\n");
		v = v->next;
		o++;
	}
	return (o);
}

/**
 * add_bl - adds a bl to the start of the list
 *
 * @str: str field of bl
 * @num: bl index used by history
 * @ldr: address of pointer to ldr bl
 *
 * Return: size of list
 */

list_t *add_bl(list_t **ldr, const char *str, int num)
{
	list_t *nw_ldr;

	if (!ldr)
		return (NULL);
	nw_ldr = malloc(sizeof(list_t));
	if (!nw_ldr)
		return (NULL);
	_memset((void *)nw_ldr, 0, sizeof(list_t));
	nw_ldr->num = num;
	if (str)
	{
		nw_ldr->str = _strdup(str);
		if (!nw_ldr->str)
		{
			free(nw_ldr);
			return (NULL);
		}
	}
	nw_ldr->next = *ldr;
	*ldr = nw_ldr;
	return (nw_ldr);
}

/**
 * rm_bl_spec - deletes nodes at given index
 *
 * @index: index of bl to delete
 * @ldr: address of pointer to first bl
 *
 * Return: 1 on success, 0 on failure
 */

int rm_bl_spec(list_t **ldr, unsigned int index)
{
	unsigned int o = 0;
	list_t *bl;
	list_t *prev_bl;

	if (!ldr || !*ldr)
		return (0);

	if (!index)
	{
		bl = *ldr;
		*ldr = (*ldr)->next;
		free(bl->str);
		free(bl);
		return (1);
	}
	bl = *ldr;
	while (bl)
	{
		if (o == index)
		{
			prev_bl->next = bl->next;
			free(bl->str);
			free(bl);
			return (1);
		}
		o++;
		prev_bl = bl;
		bl = bl->next;
	}
	return (0);
}
