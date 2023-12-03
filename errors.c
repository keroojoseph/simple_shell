#include "shell.h"

/**
 * displayErrorText - prints an error string to standard error
 * @errorText: the string to be printed
 *
 * Return: Nothing
 */
void displayErrorText(char *errorText)
{
    int idx = 0;

    if (!errorText)
        return;

    while (errorText[idx] != '\0')
    {
        writeToErrorOutput(errorText[idx]);
        idx++;
    }
}

/**
 * writeToErrorOutput - writes the character c to standard error
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeToErrorOutput(char character)
{
    static int currentIndex;
    static char buffer[WRITE_BUFFER_SIZE];

    if (character == BUFFER_FLUSH || currentIndex >= WRITE_BUFFER_SIZE)
    {
        write(2, buffer, currentIndex);
        currentIndex = 0;
    }

    if (character != BUFFER_FLUSH)
        buffer[currentIndex++] = character;

    return 1;
}

/**
 * printToSpecificFileDesc - writes the character c to a given file descriptor
 * @character: The character to print
 * @fileDesc: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printToSpecificFileDesc(char character, int fileDesc)
{
    static int currentIndex;
    static char buffer[WRITE_BUFFER_SIZE];

    if (character == BUFFER_FLUSH || currentIndex >= WRITE_BUFFER_SIZE)
    {
        write(fileDesc, buffer, currentIndex);
        currentIndex = 0;
    }

    if (character != BUFFER_FLUSH)
        buffer[currentIndex++] = character;

    return 1;
}

/**
 * printStringToFileDesc - prints an input string to a specified file descriptor
 * @stringToPrint: the string to be printed
 * @fileDesc: the file descriptor to write to
 *
 * Return: the number of characters printed
 */
int printStringToFileDesc(char *stringToPrint, int fileDesc)
{
    int idx = 0;

    if (!stringToPrint)
        return 0;

    while (*stringToPrint)
    {
        idx += printToSpecificFileDesc(*stringToPrint++, fileDesc);
    }

    return idx;
}
