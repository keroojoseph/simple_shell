#include "shell.h"

/**
 * initializeShellInfo - initializes the shell_info_t struct fields to NULL
 * @shell_info: pointer to the shell_info_t struct
 * This project made by Kero & Mark
 */
void initializeShellInfo(shell_info_t *shell_info)
{
    shell_info->arg = NULL;
    shell_info->arg_vector = NULL;
    shell_info->path = NULL;
    shell_info->arg_count = 0;
}

/**
 * setShellInfo - sets and processes the arguments in shell_info_t struct
 * @shell_info: pointer to the shell_info_t struct
 * @arg_vector: argument vector
 */
void setShellInfo(shell_info_t *shell_info, char **arg_vector)
{
    int i = 0;

    shell_info->executable_name = arg_vector[0];
    if (shell_info->arg)
    {
        shell_info->arg_vector = splitString(shell_info->arg, " \t");
        if (!shell_info->arg_vector)
        {
            shell_info->arg_vector = malloc(sizeof(char *) * 2);
            if (shell_info->arg_vector)
            {
                shell_info->arg_vector[0] = duplicateString(shell_info->arg);
                shell_info->arg_vector[1] = NULL;
            }
        }
        for (i = 0; shell_info->arg_vector && shell_info->arg_vector[i]; i++)
            ;
        shell_info->arg_count = i;

        replaceAliases(shell_info);
        replaceVariables(shell_info);
    }
}

/**
 * freeShellInfoFields - frees the fields of the shell_info_t struct based on the 'all' flag
 * @shell_info: pointer to the shell_info_t struct
 * @free_all: true if freeing all fields
 */
void freeShellInfoFields(shell_info_t *shell_info, int free_all)
{
    free(shell_info->arg_vector);
    shell_info->arg_vector = NULL;
    shell_info->path = NULL;

    if (free_all)
    {
        if (!shell_info->command_buffer)
            free(shell_info->arg);

        freeList(&(shell_info->environment));
        freeList(&(shell_info->history));
        freeList(&(shell_info->alias));
        free(shell_info->environment_copy);
        shell_info->environment_copy = NULL;

        freeBuffer((void **)shell_info->command_buffer);

        if (shell_info->read_file_descriptor > 2)
            close(shell_info->read_file_descriptor);

        flushOutputBuffer();
    }
}
