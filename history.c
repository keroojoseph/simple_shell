#include "shell.h"

/**
 * obtainHistoryFilePath - retrieves the path for the history file
 * @info: pointer to the info_t struct
 *
 * Return: string containing the history file path (allocated memory)
 */
char *obtainHistoryFilePath(info_t *info)
{
    char *buffer, *homeDir;

    homeDir = _getenv(info, "HOME=");
    if (!homeDir)
        return NULL;

    buffer = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HISTORY_FILE) + 2));
    if (!buffer)
        return NULL;

    buffer[0] = '\0';
    _strcpy(buffer, homeDir);
    _strcat(buffer, "/");
    _strcat(buffer, HISTORY_FILE);

    return buffer;
}

/**
 * saveHistoryToFile - writes history contents to a file
 * @info: pointer to the info_t struct
 *
 * Return: 1 on success, -1 on failure
 */
int saveHistoryToFile(info_t *info)
{
    ssize_t fileDesc;
    char *filename = obtainHistoryFilePath(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fileDesc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fileDesc == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        _putsToFileDescriptor(node->str, fileDesc);
        _putcharToFileDescriptor('\n', fileDesc);
    }

    _putcharToFileDescriptor(BUF_FLUSH, fileDesc);
    close(fileDesc);

    return 1;
}

/**
 * loadHistoryFromFile - reads history from a file
 * @info: pointer to the info_t struct
 *
 * Return: histcount on success, 0 on failure
 */
int loadHistoryFromFile(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fileDesc, readLen, fileSize = 0;
    struct stat fileStat;
    char *buffer = NULL, *filename = obtainHistoryFilePath(info);

    if (!filename)
        return 0;

    fileDesc = open(filename, O_RDONLY);
    free(filename);

    if (fileDesc == -1)
        return 0;

    if (!fstat(fileDesc, &fileStat))
        fileSize = fileStat.st_size;

    if (fileSize < 2)
        return 0;

    buffer = malloc(sizeof(char) * (fileSize + 1));
    if (!buffer)
        return 0;

    readLen = read(fileDesc, buffer, fileSize);
    buffer[fileSize] = '\0';

    if (readLen <= 0)
        return free(buffer), 0;

    close(fileDesc);

    for (i = 0; i < fileSize; i++)
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            addHistoryEntry(info, buffer + last, linecount++);
            last = i + 1;
        }

    if (last != i)
        addHistoryEntry(info, buffer + last, linecount++);

    free(buffer);
    info->histcount = linecount;

    while (info->histcount-- >= MAX_HISTORY)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);
    return info->histcount;
}

/**
 * addHistoryEntry - adds an entry to the history linked list
 * @info: pointer to the info_t struct
 * @buffer: string to be added
 * @linecount: the history line count (histcount)
 *
 * Return: Always 0
 */
int addHistoryEntry(info_t *info, char *buffer, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buffer, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: pointer to the info_t struct
 *
 * Return: the new histcount
 */
int renumberHistory(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return info->histcount = i;
}
