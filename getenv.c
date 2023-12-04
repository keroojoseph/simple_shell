#include "shell.h"

/**
 * duplicateEnvironment - returns the copied string array of our environment
 * @infoData: Structure containing potential arguments and environment variables.
 * Return: The copied environment string array
 * This project made by Kero & Mark
 */
char **duplicateEnvironment(info_t *infoData)
{
    if (!infoData->environment || infoData->env_changed)
    {
        infoData->environment = convertListToStringArray(infoData->env);
        infoData->env_changed = 0;
    }

    return (infoData->environment);
}

/**
 * eraseEnvironmentVariable - Remove an environment variable
 * @infoData: Structure containing potential arguments and environment variables.
 * @var: the environment variable to remove
 * Return: 1 on deletion, 0 otherwise
 */
int eraseEnvironmentVariable(info_t *infoData, char *var)
{
    list_t *currentNode = infoData->env;
    size_t index = 0;
    char *ptr;

    if (!currentNode || !var)
        return 0;

    while (currentNode)
    {
        ptr = startsWith(currentNode->str, var);
        if (ptr && *ptr == '=')
        {
            infoData->env_changed = removeNodeAtIndex(&(infoData->env), index);
            index = 0;
            currentNode = infoData->env;
            continue;
        }
        currentNode = currentNode->next;
        index++;
    }
    return infoData->env_changed;
}

/**
 * setEnvVariable - Initialize a new environment variable
 *                  or modify an existing one
 * @infoData: Structure containing potential arguments and environment variables.
 * @var: the environment variable name
 * @val: the environment variable value
 * Return: Always 0
 */
int setEnvVariable(info_t *infoData, char *var, char *val)
{
    char *buffer = NULL;
    list_t *currentNode;
    char *ptr;

    if (!var || !val)
        return 0;

    buffer = malloc(_strlen(var) + _strlen(val) + 2);
    if (!buffer)
        return 1;

    _strcpy(buffer, var);
    _strcat(buffer, "=");
    _strcat(buffer, val);

    currentNode = infoData->env;
    while (currentNode)
    {
        ptr = startsWith(currentNode->str, var);
        if (ptr && *ptr == '=')
        {
            free(currentNode->str);
            currentNode->str = buffer;
            infoData->env_changed = 1;
            return 0;
        }
        currentNode = currentNode->next;
    }

    addNodeEnd(&(infoData->env), buffer, 0);
    free(buffer);
    infoData->env_changed = 1;
    return 0;
}
