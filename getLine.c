#include "shell.h"

/**
 * bufferChainedCmds - buffers chained commands
 * @shell_info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 * Return: bytes read
 * This project made by Kero & Mark
 */
ssize_t bufferChainedCmds(shell_info_t *shell_info, char **buffer, size_t *length)
{
    ssize_t bytes_read = 0;
    size_t length_position = 0;

    if (!*length)
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handleSIGINT);

#if USE_GETLINE
        bytes_read = getline(buffer, &length_position, stdin);
#else
        bytes_read = _getline(shell_info, buffer, &length_position);
#endif

        if (bytes_read > 0)
        {
            if ((*buffer)[bytes_read - 1] == '\n')
            {
                (*buffer)[bytes_read - 1] = '\0'; // Remove trailing newline
                bytes_read--;
            }

            shell_info->line_count_flag = 1;
            removeComments(*buffer);
            buildHistoryList(shell_info, *buffer, shell_info->hist_count++);

            *length = bytes_read;
            shell_info->cmd_buf = buffer;
        }
    }
    return bytes_read;
}

/**
 * getInput - gets a line minus the newline
 * @shell_info: parameter struct
 * Return: bytes read
 */
ssize_t getInput(shell_info_t *shell_info)
{
    static char *buffer; // The ';' command chain buffer
    static size_t i, j, length;
    ssize_t bytes_read = 0;
    char **buffer_ptr = &(shell_info->arg), *ptr;

    _putchar(BUF_FLUSH);
    bytes_read = bufferChainedCmds(shell_info, &buffer, &length);

    if (bytes_read == -1) // EOF
        return -1;

    if (length)
    {
        j = i;
        ptr = buffer + i;

        checkChain(shell_info, buffer, &j, i, length);

        while (j < length)
        {
            if (isChain(shell_info, buffer, &j))
                break;
            j++;
        }

        i = j + 1;

        if (i >= length)
        {
            i = length = 0;
            shell_info->cmd_buf_type = CMD_NORMAL;
        }

        *buffer_ptr = ptr;
        return _strlen(ptr);
    }

    *buffer_ptr = buffer;
    return bytes_read;
}

/**
 * readBuffer - reads a buffer
 * @shell_info: parameter struct
 * @buffer: buffer
 * @size: size
 * Return: bytesRead
 */
ssize_t readBuffer(shell_info_t *shell_info, char *buffer, size_t *size)
{
    ssize_t bytes_read = 0;

    if (*size)
        return 0;

    bytes_read = read(shell_info->read_fd, buffer, READ_BUFFER_SIZE);
    if (bytes_read >= 0)
        *size = bytes_read;

    return bytes_read;
}

/**
 * _getline - gets the next line of input from STDIN
 * @shell_info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: size
 */
int _getline(shell_info_t *shell_info, char **ptr, size_t *length)
{
    static char buf[READ_BUFFER_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0, size = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        size = *length;

    if (i == len)
        i = len = 0;

    bytes_read = readBuffer(shell_info, buf, &len);

    if (bytes_read == -1 || (bytes_read == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = _realloc(p, size, size ? size + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (size)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    size += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = size;

    *ptr = p;
    return size;
}

/**
 * handleSIGINT - blocks ctrl-C
 * @signal_num: the signal number
 * Return: void
 */
void handleSIGINT(__attribute__((unused)) int signal_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
