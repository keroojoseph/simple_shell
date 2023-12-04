#include "shell.h"

/**
 * shellLoop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * This project made by Kero & Mark
 * Return: 0 on success, 1 on error, or error code
 */
int shellLoop(info_t *info, char **av) {
    ssize_t readStatus = 0;
    int builtinResult = 0;

    while (readStatus != -1 && builtinResult != -2) {
        clearInfo(info);

        if (isInteractive(info))
            _puts("$ ");

        _eputchar(BUF_FLUSH);
        readStatus = getInput(info);

        if (readStatus != -1) {
            setInfo(info, av);
            builtinResult = findBuiltin(info);

            if (builtinResult == -1)
                findCommand(info);
        } else if (isInteractive(info))
            _putchar('\n');

        freeInfo(info, 0);
    }

    writeHistory(info);
    freeInfo(info, 1);

    if (!isInteractive(info) && info->status)
        exit(info->status);

    if (builtinResult == -2) {
        if (info->errNum == -1)
            exit(info->status);
        exit(info->errNum);
    }

    return builtinResult;
}

/**
 * findBuiltin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int findBuiltin(info_t *info) {
    int index, builtinResult = -1;
    builtinTable builtInTable[] = {
        {"exit", _myExit},
        {"env", _myEnv},
        {"help", _myHelp},
        {"history", _myHistory},
        {"setenv", _mySetEnv},
        {"unsetenv", _myUnsetEnv},
        {"cd", _myCd},
        {"alias", _myAlias},
        {NULL, NULL}
    };

    for (index = 0; builtInTable[index].type; index++) {
        if (_strcmp(info->argv[0], builtInTable[index].type) == 0) {
            info->lineCount++;
            builtinResult = builtInTable[index].func(info);
            break;
        }
    }

    return builtinResult;
}

/**
 * findCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(info_t *info) {
    char *path = NULL;
    int i, count = 0;

    info->path = info->argv[0];

    if (info->lineCountFlag == 1) {
        info->lineCount++;
        info->lineCountFlag = 0;
    }

    for (i = 0; info->arg[i]; i++) {
        if (!isDelimiter(info->arg[i], " \t\n"))
            count++;
    }

    if (!count)
        return;

    path = findPath(info, _getEnv(info, "PATH="), info->argv[0]);

    if (path) {
        info->path = path;
        forkCommand(info);
    } else {
        if ((isInteractive(info) || _getEnv(info, "PATH=") || info->argv[0][0] == '/') &&
            isCmd(info, info->argv[0]))
            forkCommand(info);
        else if (*(info->arg) != '\n') {
            info->status = 127;
            printError(info, "not found\n");
        }
    }
}

/**
 * forkCommand - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(info_t *info) {
    pid_t childPid;

    childPid = fork();

    if (childPid == -1) {
        perror("Error:");
        return;
    }

    if (childPid == 0) {
        if (execve(info->path, info->argv, getEnviron(info)) == -1) {
            freeInfo(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    } else {
        wait(&(info->status));

        if (WIFEXITED(info->status)) {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                printError(info, "Permission denied\n");
        }
    }
}
