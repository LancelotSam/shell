#include "shell.h"
/**
 * _atoi-this is the main function
 *
 * It converts a str to int
 * @str:the string to be converted
 * Return: integer of converted string
 */
int _atoi(const char *str)
{
	int i = 0, reslt = 0, sign = 1;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		sign = 1;
		i++;
	}

	for (; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			/*iteratig t right means shifting digits to left*/
			/*this multiplies the number by 10 (base 10)*/
			/*str[i] - '\0', subtracts ascii val of 0,i.e 48*/
			reslt = reslt * 10 + str[i] - '0';
		}
	}
	return (reslt);
}
/**
 * my_exit-this is the main function
 *
 * It exits with an integer status
 * @args:the expected exit argument to cmd line
 * Return: int exit status
 */
int my_exit(char *args[])
{
	if (args[1])
	{
		return (_atoi(args[1]));
	}
	else
	{
		return (0);
	}
}
