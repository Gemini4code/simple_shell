#include "ssp_shell.h"

/**
 * ptr_null - frees a pointer and NULLs the address
 *              space of the pointer
 *
 * @_addr_ptr: address of the pointer to free
 *
 * Return: 1 means free, 0 means otherwise.
 */

int ptr_null(void **_addr_ptr)
{
	if (_addr_ptr && *_addr_ptr)
	{
		free(*_addr_ptr);
		*_addr_ptr = NULL;

		return (1);
	}
	return (0);
}
