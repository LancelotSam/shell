#include "shell.h"
/**
 * main-this is the main function
 *
 * It runs he interactive and non-interactive shells
 *@argc: the number of commands
 *@argv:the array of arguments
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	my_shell();
  
return (0);
}
/*	int fd = STDIN_FILENO;

	if (isatty(fd) == 1)
	{
		_interactive(argv[0]);
	}
	else
	{
		_noninteractive(argv[0]);
	}
	return (0);
}*/
