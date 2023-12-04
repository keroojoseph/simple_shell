#include "shell.h"

/**
 * getListSize - determines the size of a linked list
 * @head: pointer to the first node
 * This project made by Kero & Mark
 * Return: size of the list
 */
size_t getListSize(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

/**
 * convertListToStringArray - returns an array of strings from the list's str field
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **convertListToStringArray(list_t *head)
{
    list_t *node = head;
    size_t size = getListSize(head);
    size_t i;
    char **stringsArray;
    char *str;

    if (!head || !size)
        return NULL;

    stringsArray = malloc(sizeof(char *) * (size + 1));
    if (!stringsArray)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(stringsArray[j]);
            free(stringsArray);
            return NULL;
        }

        str = _strcpy(str, node->str);
        stringsArray[i] = str;
    }
    stringsArray[i] = NULL;

    return stringsArray;
}

/**
 * printFullList - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t printFullList(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convertNumber(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * findNodeStartingWith - finds a node whose string starts with a prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *findNodeStartingWith(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = startsWith(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}
