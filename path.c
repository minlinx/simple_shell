#include "main.h"


/**
 * PathToList - Convert the path to a sing list
 * @head: the list
 * @path: the path
 * Return: SUCCESS or Error
 */

int PathToList(list_t **head, char *path)
{
	char *path_cpy = _strdup(path);
	char *tmp;

	if (path == NULL)
		return (-1);

	tmp = _strtok(path_cpy, ":");
	while (tmp)
	{
		add_node_end(head, tmp);
		tmp = _strtok(NULL, ":");
	}

	free(path_cpy);
	return (0);
}

/**
 * cmd_to_path - converts a cmd to full path
 * @head: the path list
 * @command: the cmd to convert
 * Return: the full cmd path
 */

char *cmd_to_path(list_t *head, char *command)
{
	char buff[1024];
	list_t *current;
	struct stat st;

	current = head;
	while (current)
	{
		_strcpy(buff, current->path);
		_strcat(buff, "/");
		_strcat(buff, command);
		if (stat(buff, &st) == 0)
		{
			command = _strdup(buff);
			return (command);
		}
		_strcpy(buff, "");
		current = current->next;
	}

	return (NULL);
}

/**
 * get_cmd - extracts the first cmd token
 * @head: the path list
 * @str: the line
 * @exit_code: the exit code
 * @exec_err: the error output
 * @name: the name of the program
 * @ncmd: the number of consecutive commands
 * Return: the command
 */
char *get_cmd(list_t *head, char *str, int *exit_code, char *exec_err,
		char *name, size_t ncmd)
{
	char *tmp = str;
	int i = 0, j = 0;
	char buf[64];
	char *cmd, *tmp_cmd, *err_cmd, *cmd_path;
	struct stat st;

	for (; tmp[i] != ' ' && tmp[i]; j++, i++)
		buf[j] = tmp[i];
	buf[j] = '\0';

	cmd = _strdup(buf);
	if (cmd[0] == '\0')
		return (cmd);
	err_cmd = cmd;

	if (stat(cmd, &st) == -1)
	{
		cmd_path = cmd_to_path(head, cmd);

		if (cmd_path != NULL)
		{
			tmp_cmd = _strdup(cmd_path);
			free(cmd_path);

		}
		else
			tmp_cmd = NULL;
		if (tmp_cmd == NULL)
		{
			error_exec(exec_err, name, ncmd, err_cmd);
			write(STDERR_FILENO, exec_err, _strlen(exec_err));
			*exit_code = 127;
		}
		free(cmd);
		return (tmp_cmd);
	}
	return (cmd);
}
