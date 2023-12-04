#include "shell.h"

/**
 * copyString - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the number of characters to be copied
 * Return: the concatenated string
 * This project made by Kero & Mark
 */
char *copyString(char *dest, char *src, int n)
{
    int idx_dest = 0, idx_src = 0;
    char *start = dest;

    while (src[idx_src] != '\0' && idx_src < n - 1)
    {
        dest[idx_dest] = src[idx_src];
        idx_dest++;
        idx_src++;
    }

    if (idx_src < n)
    {
        int j = idx_src;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return start;
}

/**
 * concatenateStrings - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of bytes to be used
 * Return: the concatenated string
 */
char *concatenateStrings(char *dest, char *src, int n)
{
    int idx_dest = 0, idx_src = 0;
    char *start = dest;

    while (dest[idx_dest] != '\0')
        idx_dest++;

    while (src[idx_src] != '\0' && idx_src < n)
    {
        dest[idx_dest] = src[idx_src];
        idx_dest++;
        idx_src++;
    }

    if (idx_src < n)
        dest[idx_dest] = '\0';

    return start;
}

/**
 * findCharacter - locates a character in a string
 * @str: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the memory area of the character in the string
 */
char *findCharacter(char *str, char c)
{
    do
    {
        if (*str == c)
            return str;
    } while (*str++ != '\0');

    return NULL;
}
