#include "shell.h"

/**
 * isChainDelimiter - test if the current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int isChainDelimiter(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return 0;
	}
	*p = j;
	return 1;
}

/**
 * checkChain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replaceAlias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
		{
			return 0;
		}
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
		{
			return 0;
		}
		p = _strdup(p + 1);
		if (!p)
		{
			return 0;
		}
		info->argv[0] = p;
	}
	return 1;
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			continue;
		}

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]), _strdup(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]), _strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(""));
	}
	return 0;
}

/**
 * replaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return 1;
}
