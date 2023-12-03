#include "shell.h"

/**
 * stringLength - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int stringLength(char *s) {
    int length = 0;

    if (!s)
        return 0;

    while (*s++) {
        length++;
    }
    return length;
}

/**
 * stringCompare - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int stringCompare(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * stringStartsWith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *stringStartsWith(const char *haystack, const char *needle) {
    while (*needle) {
        if (*needle++ != *haystack++)
            return NULL;
    }
    return (char *)haystack;
}

/**
 * stringConcatenate - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *stringConcatenate(char *dest, char *src) {
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return ret;
}
