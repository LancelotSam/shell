#include "shell.h"
/**
 * _parse_input-this is the main function
 *
 * It parses the input from lineptr
 * @lineptr:pointer containing the user input
 * Return: char arguments input
 */
char **_parse_input(char *lineptr)
{
	const char delimiter[] = " ,;:-|";
	int args_index = 0;
	char *token;
	char **args_input;

	args_input = malloc(sizeof(char *) * (MAX_ARGS + 1));

	if (args_input == NULL)
		return (NULL);
	token = strtok(lineptr, delimiter);
	while (token != NULL && args_index < MAX_ARGS - 1)
	{
		if (_strlen(token) >= MAX_TOTAL_LENGTH)
		{
			perror("Argument too long\n");
			break;
		}
		args_input[args_index++] = _strdup(token);
		token = strtok(NULL, delimiter);
	}
	args_input[args_index] = '\0';

	return (args_input);
}
/**
 * **get_path-this is the main function
 *
 * it gets the path
 * Return: character path tokens
 */
char **get_path()
{

	char *main_path = getenv("PATH");
	int i = 0, j = 0;

	char *path_cpy = _strdup(main_path);
	char *dir;
	char **path_tokens = malloc(sizeof(char *) * (MAX_ARGS + 1));

	if (main_path == NULL)
	{
		perror("Path does not exist");
		return (NULL);
	}
	if (path_tokens == NULL)
	{
		perror("Mem allocatin failed");
		return (NULL);
	}

	dir = strtok(path_cpy, ":");
	while (dir != NULL && i < MAX_PATHS - 1)
	{
		path_tokens[i] = _strdup(dir);
		if (path_tokens[i] == NULL)
		{
			perror("Error duplicating tokens");
			for (; j < i; j++)
			{
				free(path_tokens[j]);
			}
			free(path_tokens);
			free(path_cpy);

			return (NULL);
		}
		dir = strtok(NULL, ":");
		i++;
	}
	path_tokens[i] = '\0';

	free(path_cpy);

	return (path_tokens);
}
/**
 * _parse_path-this is the main function
 *
 * It parse steh gotten pat
 * @path_tokens: tokenized path
 * @args_input: arguments input
 * @full_path: the total length of path
 * Return:void
 */
void _parse_path(char **path_tokens, char **args_input, char full_path[][MAX_TOTAL_LENGTH])
{
	int ind = 0, path_len;

	for (; path_tokens[ind] != NULL; ind++)
	{
		path_len = _strlen(path_tokens[ind]);
		if (path_len + _strlen(args_input[0]) + 1 >= MAX_TOTAL_LENGTH)
		{
			perror("Path too long, increase buffer\n");
			return;
		}

		snprintf(full_path[ind], MAX_TOTAL_LENGTH, "%s/%s", path_tokens[ind], args_input[0]);
	}
}
/**
 * shell-this is the main function
 *
 * It is a custom simple shell
 * Return: void
 */
void my_shell()
{
	const char prompt[] = "(MYShell) $ ";
	size_t buff_size = 0;
	char *lineptr = NULL;
	ssize_t read_chars;
	char **path_tokens;
	int path_index = 0;
	int i = 0;
	char **args_input;
	/*char * const argv[] = {args_input[0], NULL};*/
	char full_path[MAX_PATHS][MAX_TOTAL_LENGTH];
	char **new_argv;
	int cmd_found;


	while (1)
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));

		read_chars = getline(&lineptr, &buff_size, stdin);

		if (read_chars == -1 || read_chars == EOF)
		{
			perror("Nothing was entered");
			free(lineptr);
			continue;
		}
		if (read_chars == 1)
		{
			perror("Not a cmd");
			free(lineptr);
			continue;
		}

		if (lineptr[read_chars - 1] == '\n')
		{
			lineptr[read_chars - 1] = '\0';
		}		

		path_tokens = get_path();

		if (path_tokens == NULL)
		{
			free(lineptr);
			continue;
		}

		args_input = _parse_input(lineptr);

		_parse_path(path_tokens, args_input, full_path);

		while (path_tokens[path_index] != NULL) {
			pid_t PID = fork();

			if (PID == 0) {
				for (i = 0; full_path[i][0] != '\0'; i++) {
					if (access(full_path[i], X_OK) == 0) 
					{
						cmd_found = 0;
						new_argv = malloc(sizeof(char *) * 2);
						if (new_argv == NULL) {
							perror("malloc");
							exit(EXIT_FAILURE);
						}
						new_argv[0] = args_input[0];
						new_argv[1] = NULL;

						execve(full_path[i], new_argv, NULL);
						perror("execve"); /*if execve fails*/

						free(new_argv);
					} else {
						fprintf(stderr, "Command not found: %s\n", args_input[0]);
					}
				}

				if (!cmd_found) {
					fprintf(stderr, "Command not found: %s\n", args_input[0]);
				}

				exit(EXIT_FAILURE); /* Exit child process*/
			} else if (PID == -1) {
				perror("fork");
				break;
			} else {
				wait(NULL); /* Wait for the child to complete*/
			}

			path_index++;
		}

		path_index = 0;
	}

	free(lineptr);

	for (i = 0; path_tokens[i] != NULL; i++)
	{
		free(path_tokens[i]);
	}
	free(path_tokens);

	}
