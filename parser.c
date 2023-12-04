#include "shell.h"

/**
 * isFileExecutable - checks if a file is an executable command
 * @info: the information struct
 * @filepath: the path to the file
 * This project made by Kero & Mark
 * Return: 1 if true, 0 otherwise
 */
int isFileExecutable(info_t *info, char *filepath)
{
    struct stat file_stat;

    (void)info;
    if (!filepath || stat(filepath, &file_stat) != 0)
        return 0;

    return S_ISREG(file_stat.st_mode) != 0;
}

/**
 * copySubstring - duplicates characters within a string
 * @source: the source string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer
 */
char *copySubstring(const char *source, int start, int stop)
{
    static char buffer[1024];
    int k = 0;

    for (int i = start; i < stop; i++)
    {
        if (source[i] != ':')
        {
            buffer[k++] = source[i];
        }
    }
    buffer[k] = '\0';
    return buffer;
}

/**
 * findExecutableInPath - finds the command in the PATH string
 * @info: the information struct
 * @pathstr: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found, otherwise NULL
 */
char *findExecutableInPath(info_t *info, const char *pathstr, const char *command)
{
    int index = 0, startPos = 0;
    char *path;

    if (!pathstr)
        return NULL;

    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (isFileExecutable(info, command))
            return command;
    }

    while (1)
    {
        if (!pathstr[index] || pathstr[index] == ':')
        {
            path = copySubstring(pathstr, startPos, index);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (isFileExecutable(info, path))
                return path;
            if (!pathstr[index])
                break;
            startPos = index;
        }
        index++;
    }
    return NULL;
}
