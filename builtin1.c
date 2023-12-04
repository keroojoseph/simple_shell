#include "shell.h"

/**
 * showCommandHistory - displays the history list with line numbers
 * @info_command: Structure containing potential arguments.
 * Return: Always returns 0
 * This project made by Kero & Mark
 */
int showCommandHistory(command_info_t *info_command)
{
    displayList(info_command->command_history);
    return 0;
}

/**
 * eliminateAlias - removes an alias identified by a string
 * @info_command: parameter structure
 * @aliasStr: string representing the alias
 * Return: Returns 0 on success, 1 on error
 */
int eliminateAlias(command_info_t *info_command, char *aliasStr)
{
    char *ptr, character;
    int result;

    ptr = findCharacter(aliasStr, '=');
    if (!ptr)
        return 1;

    character = *ptr;
    *ptr = 0;
    result = removeNodeAtIndex(&(info_command->aliases),
                               getNodeIndex(info_command->aliases, nodeStartsWith(info_command->aliases, aliasStr, -1)));
    *ptr = character;
    return result;
}

/**
 * establishAlias - sets an alias to a string
 * @info_command: parameter structure
 * @aliasStr: string representing the alias
 * Return: Returns 0 on success, 1 on error
 */
int establishAlias(command_info_t *info_command, char *aliasStr)
{
    char *ptr;

    ptr = findCharacter(aliasStr, '=');
    if (!ptr)
        return 1;
    if (!*++ptr)
        return eliminateAlias(info_command, aliasStr);

    eliminateAlias(info_command, aliasStr);
    return (addNodeEnd(&(info_command->aliases), aliasStr, 0) == NULL);
}

/**
 * revealAlias - prints an alias string
 * @aliasNode: the alias node
 * Return: Returns 0 on success, 1 on error
 */
int revealAlias(list_t *aliasNode)
{
    char *ptr = NULL, *alias = NULL;

    if (aliasNode)
    {
        ptr = findCharacter(aliasNode->str, '=');
        for (alias = aliasNode->str; alias <= ptr; alias++)
            printCharacter(*alias);
        printCharacter('\'');
        printString(ptr + 1);
        printString("'\n");
        return 0;
    }
    return 1;
}

/**
 * handleAlias - manages the alias functionality similar to the built-in 'alias'
 * @info_command: Structure containing potential arguments.
 * Return: Always returns 0
 */
int handleAlias(command_info_t *info_command)
{
    int index = 0;
    char *ptr = NULL;
    list_t *aliasNode = NULL;

    if (info_command->argCount == 1)
    {
        aliasNode = info_command->aliases;
        while (aliasNode)
        {
            revealAlias(aliasNode);
            aliasNode = aliasNode->next;
        }
        return 0;
    }

    for (index = 1; info_command->arguments[index]; index++)
    {
        ptr = findCharacter(info_command->arguments[index], '=');
        if (ptr)
            establishAlias(info_command, info_command->arguments[index]);
        else
            revealAlias(nodeStartsWith(info_command->aliases, info_command->arguments[index], '='));
    }
    return 0;
}
