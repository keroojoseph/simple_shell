#include "shell.h"

/**
 * determineInteractive - verifies if the shell is in interactive mode
 * @infoPtr: pointer to the structure
 * Return: 1 if in interactive mode, 0 otherwise
 * This project made by Kero & Mark
 */
int determineInteractive(info_t *infoPtr)
{
    return (isatty(STDIN_FILENO) && infoPtr->read_file_desc <= 2);
}

/**
 * isSeparator - checks if a character is a separator
 * @charValue: the character to examine
 * @separatorStr: string holding separators
 * Return: 1 if true, 0 if false
 */
int isSeparator(char charValue, char *separatorStr)
{
    while (*separatorStr)
        if (*separatorStr++ == charValue)
            return (1);
    return (0);
}

/**
 * verifyAlphabetic - checks for an alphabetic character
 * @character: The character to inspect
 * Return: 1 if 'character' is alphabetic, 0 otherwise
 */
int verifyAlphabetic(int character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * convertStringToInt - transforms a string to an integer
 * @inputString: the string to convert
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int convertStringToInt(char *inputString)
{
    int index, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (index = 0; inputString[index] != '\0' && flag != 2; index++)
    {
        if (inputString[index] == '-')
            sign *= -1;

        if (inputString[index] >= '0' && inputString[index] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (inputString[index] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
