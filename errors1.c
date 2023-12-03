#include "shell.h"

/**
 * convertStringToInt - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 *       -1 on error
 */
int convertStringToInt(char *str)
{
    int idx = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;

    for (idx = 0; str[idx] != '\0'; idx++)
    {
        if (str[idx] >= '0' && str[idx] <= '9')
        {
            result *= 10;
            result += (str[idx] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }
    return (int)result;
}

/**
 * displayErrorMessage - prints an error message
 * @infoData: the parameter & return info data
 * @errStr: string containing specified error type
 * Return: Nothing
 */
void displayErrorMessage(info_t *infoData, char *errStr)
{
    printErrorString(infoData->filename);
    printErrorString(": ");
    printDecimal(infoData->line_count, STDERR_FILENO);
    printErrorString(": ");
    printErrorString(infoData->arguments[0]);
    printErrorString(": ");
    printErrorString(errStr);
}

/**
 * printInteger - prints a decimal (integer) number (base 10)
 * @number: the input
 * @fileDesc: the file descriptor to write to
 * Return: number of characters printed
 */
int printInteger(int number, int fileDesc)
{
    int (*printChar)(char) = printCharacter;
    int i, count = 0;
    unsigned int absolute, current;

    if (fileDesc == STDERR_FILENO)
        printChar = printErrorCharacter;

    if (number < 0)
    {
        absolute = -number;
        printChar('-');
        count++;
    }
    else
        absolute = number;

    current = absolute;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute / i)
        {
            printChar('0' + current / i);
            count++;
        }
        current %= i;
    }
    printChar('0' + current);
    count++;

    return count;
}

/**
 * convertIntToString - converts a number to a string
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string representation of the number
 */
char *convertIntToString(long int num, int base, int flags)
{
    static char *charArray;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    charArray = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = charArray[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * eliminateComments - replaces the first instance of '#' with '\0'
 * @inputBuffer: address of the string to modify
 * Return: Always 0
 */
void eliminateComments(char *inputBuffer)
{
    int i;

    for (i = 0; inputBuffer[i] != '\0'; i++)
    {
        if (inputBuffer[i] == '#' && (!i || inputBuffer[i - 1] == ' '))
        {
            inputBuffer[i] = '\0';
            break;
        }
    }
}
