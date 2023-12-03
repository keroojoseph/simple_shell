#include "shell.h"

/**
 * prependNode - adds a node to the start of the list
 * @head: pointer to the head node
 * @str: string field of the node
 * @num: node index used by history
 *
 * Return: pointer to the new head of the list
 */
list_t *prependNode(list_t **head, const char *str, int num)
{
    list_t *newHead;

    if (!head)
        return NULL;

    newHead = malloc(sizeof(list_t));
    if (!newHead)
        return NULL;

    _memset((void *)newHead, 0, sizeof(list_t));
    newHead->num = num;

    if (str)
    {
        newHead->str = _strdup(str);
        if (!newHead->str)
        {
            free(newHead);
            return NULL;
        }
    }

    newHead->next = *head;
    *head = newHead;

    return newHead;
}

/**
 * appendNode - adds a node to the end of the list
 * @head: pointer to the head node
 * @str: string field of the node
 * @num: node index used by history
 *
 * Return: pointer to the new node added to the end
 */
list_t *appendNode(list_t **head, const char *str, int num)
{
    list_t *newNode, *currentNode;

    if (!head)
        return NULL;

    currentNode = *head;
    newNode = malloc(sizeof(list_t));
    if (!newNode)
        return NULL;

    _memset((void *)newNode, 0, sizeof(list_t));
    newNode->num = num;

    if (str)
    {
        newNode->str = _strdup(str);
        if (!newNode->str)
        {
            free(newNode);
            return NULL;
        }
    }

    if (currentNode)
    {
        while (currentNode->next)
            currentNode = currentNode->next;
        currentNode->next = newNode;
    }
    else
        *head = newNode;

    return newNode;
}

/**
 * printListStrings - prints only the str element of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of list
 */
size_t printListStrings(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * deleteNodeAtIndex - deletes a node at a given index
 * @head: pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *node, *prevNode;
    unsigned int count = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    node = *head;
    while (node)
    {
        if (count == index)
        {
            prevNode->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }
        count++;
        prevNode = node;
        node = node->next;
    }
    return 0;
}

/**
 * freeEntireList - frees all nodes of a list
 * @headPtr: pointer to the head node
 *
 * Return: void
 */
void freeEntireList(list_t **headPtr)
{
    list_t *node, *nextNode, *head;

    if (!headPtr || !*headPtr)
        return;

    head = *headPtr;
    node = head;
    while (node)
    {
        nextNode = node->next;
        free(node->str);
        free(node);
        node = nextNode;
    }
    *headPtr = NULL;
}
