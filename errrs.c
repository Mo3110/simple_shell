#include "shell.h"
/**
 * ok_eputs - Entry function that prints an input str
 * @str: variable of the string to be printed
 * Return: -
 */
void ok_eputs(char *str)
{
	int j = 0;

	if (!str)
	return;
	while (str[j] != '\0')
	{
		ok_eputschar(str[j]);
		j++;
	}
}

/**
 * ok_eputschar - Entry function that writes the character c to stderr
 * @o: Variable of the char to print
 * Return: Always 1 for success, errors -1
 */
int ok_eputschar(char o)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (o == BUFF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (o != BUF_FLUSH)
		buf[j++] = o;
	return (1);
}

/**
 * ok_putfd - Entry function that writes the char o to file description
 * @o: Variable of char to print
 * Return: Always 1 for success
 */
int ok_putfd(char o, int fd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];
	
	if (o != BUF_FLUSH)
		BUFF[J++] = o;
	return (1);
}

/**
 * ok_putsfd - Entry func that prints an input string
 * @str: variable to the string to be printed
 * @fd: Variable of tiledescriptor
 * Return: Nuncer of chars
 */
int ok_putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += ok_putfd(*str++, fd);
	}
	return (1);
}
