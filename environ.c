#include "shell.h"

/**
 * showCurrentEnvironment - prints the current environment
 * @data_info: Structure containing potential arguments
 * Return: Always returns 0
 */
int showCurrentEnvironment(info_t *data_info)
{
    printStringList(data_info->environment);
    return 0;
}

/**
 * accessEnvironmentVariable - gets the value of an environment variable
 * @data_info: Structure containing potential arguments
 * @env_name: environment variable name
 * Return: Returns the value
 */
char *accessEnvironmentVariable(info_t *data_info, const char *env_name)
{
    list_t *current_node = data_info->environment;
    char *ptr;

    while (current_node)
    {
        ptr = startsWith(current_node->str, env_name);
        if (ptr && *ptr)
            return ptr;
        current_node = current_node->next;
    }
    return NULL;
}

/**
 * modifyEnvironmentVariable - Initializes a new environment variable or modifies an existing one
 * @data_info: Structure containing potential arguments
 * Return: Always returns 0
 */
int modifyEnvironmentVariable(info_t *data_info)
{
    if (data_info->arg_count != 3)
    {
        printError("_displayError", "Incorrect number of arguments\n");
        return 1;
    }
    if (_setEnvironment(data_info, data_info->arguments[1], data_info->arguments[2]))
        return 0;
    return 1;
}

/**
 * eraseEnvironmentVariable - Removes an environment variable
 * @data_info: Structure containing potential arguments
 * Return: Always returns 0
 */
int eraseEnvironmentVariable(info_t *data_info)
{
    int i;

    if (data_info->arg_count == 1)
    {
        printError("_displayError", "Too few arguments.\n");
        return 1;
    }

    for (i = 1; i <= data_info->arg_count; i++)
        _unsetEnvironment(data_info, data_info->arguments[i]);

    return 0;
}

/**
 * fillEnvironmentList - Populates the environment linked list
 * @data_info: Structure containing potential arguments
 * Return: Always returns 0
 */
int fillEnvironmentList(info_t *data_info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);

    data_info->environment = node;
    return 0;
}
