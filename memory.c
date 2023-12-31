#include "shell.h"

/**
 * freeAndSetNull - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 * This project made by Kero & Mark
 * Return: 1 if freed, otherwise 0
 * This project made by Kero & Mark
 */
int freeAndSetNull(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return 1;
	}
	return 0;
}
