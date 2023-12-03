#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = {INFO_INIT};
	int fileDescriptor = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fileDescriptor)
		: "r"(fileDescriptor));

	if (argc == 2)
	{
		fileDescriptor = open(argv[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return EXIT_FAILURE;
		}
		info->readfd = fileDescriptor;
	}

	populateEnvironmentList(info);
	readShellHistory(info);
	hsh(info, argv);
	return EXIT_SUCCESS;
}
