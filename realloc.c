#include "shell.h"

/**
 * fillMemory - fills memory with a constant byte
 * @destination: the pointer to the memory area
 * @byte: the byte to fill *destination with
 * @numBytes: the number of bytes to be filled
 * Return: a pointer to the memory area destination
 */
char *fillMemory(char *destination, char byte, unsigned int numBytes)
{
    unsigned int i;

    for (i = 0; i < numBytes; i++)
        destination[i] = byte;
    return destination;
}

/**
 * freeStringArray - frees a string array
 * @array: string array to free
 */
void freeStringArray(char **array)
{
    char **temp = array;

    if (!array)
        return;

    while (*array)
        free(*array++);

    free(temp);
}

/**
 * customReallocate - reallocates a block of memory
 * @ptr: pointer to the previously allocated block
 * @oldSize: byte size of the previous block
 * @newSize: byte size of the new block
 * Return: pointer to the reallocated block
 */
void *customReallocate(void *ptr, unsigned int oldSize, unsigned int newSize)
{
    char *newPtr;

    if (!ptr)
        return malloc(newSize);

    if (!newSize)
        return free(ptr), NULL;

    if (newSize == oldSize)
        return ptr;

    newPtr = malloc(newSize);
    if (!newPtr)
        return NULL;

    oldSize = oldSize < newSize ? oldSize : newSize;
    while (oldSize--)
        newPtr[oldSize] = ((char *)ptr)[oldSize];

    free(ptr);
    return newPtr;
}
