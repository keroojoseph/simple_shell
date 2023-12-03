#include "shell.h"

/**
 * closeShell - closes the shell
 * @info_data: Structure containing potential arguments
 * Return: Exits with the given exit status (0) if info_data.argv[0] != "exit"
 */
int closeShell(info_t *info_data)
{
    int exit_status;

    if (info_data->arguments[1]) /* If an exit argument exists */
    {
        exit_status = obtainErrorCode(info_data->arguments[1]);
        if (exit_status == -1)
        {
            info_data->status = 2;
            revealError(info_data, "Invalid number: ");
            printErrorMessage(info_data->arguments[1]);
            printNewLine();
            return 1;
        }
        info_data->error_code = obtainErrorCode(info_data->arguments[1]);
        return -2;
    }
    info_data->error_code = -1;
    return -2;
}

/**
 * alterDirectory - modifies the current directory of the process
 * @info_data: Structure containing potential arguments
 * Return: Always returns 0
 */
int alterDirectory(info_t *info_data)
{
    char *existing_dir, *new_directory, buffer[1024];
    int result_chdir;

    existing_dir = obtainCurrentWorkingDirectory(buffer, 1024);
    if (!existing_dir)
        displayErrorMessage("TODO: >>getcwd failure emsg here<<\n");

    if (!info_data->arguments[1])
    {
        new_directory = grabEnvironmentVariable(info_data, "HOME=");
        if (!new_directory)
            result_chdir = modifyDirectory((new_directory = grabEnvironmentVariable(info_data, "PWD=")) ? new_directory : "/");
        else
            result_chdir = modifyDirectory(new_directory);
    }
    else if (compareStrings(info_data->arguments[1], "-") == 0)
    {
        if (!grabEnvironmentVariable(info_data, "OLDPWD="))
        {
            displayString(existing_dir);
            printNewLine();
            return 1;
        }
        displayString(grabEnvironmentVariable(info_data, "OLDPWD="));
        printNewLine();
        result_chdir = modifyDirectory((new_directory = grabEnvironmentVariable(info_data, "OLDPWD=")) ? new_directory : "/");
    }
    else
        result_chdir = modifyDirectory(info_data->arguments[1]);

    if (result_chdir == -1)
    {
        displayErrorMessage("can't cd to ");
        printErrorMessage(info_data->arguments[1]);
        printNewLine();
    }
    else
    {
        adjustEnvironmentVariable(info_data, "OLDPWD", grabEnvironmentVariable(info_data, "PWD="));
        adjustEnvironmentVariable(info_data, "PWD", obtainCurrentWorkingDirectory(buffer, 1024));
    }
    return 0;
}

/**
 * revealAssistance - displays assistance information
 * @info_data: Structure containing potential arguments
 * Return: Always returns 0
 */
int revealAssistance(info_t *info_data)
{
    char **args_array;

    args_array = info_data->arguments;
    displayString("help call works. Function not yet implemented \n");
    if (0)
        displayString(*args_array); /* temporary unused workaround */
    return 0;
}
