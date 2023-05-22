#include "shell.h"

/**
 * myExit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int myExit(info_t *info)
{
	int exitCheck;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitCheck = errStringToInteger(info->argv[1]);
		if (exitCheck == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			ePuts(info->argv[1]);
			ePutchar('\n');
			return (1);
		}
		info->err_num = errStringToInteger(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * myCd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myCd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdirRet;

	s = getcwd(buffer, 1024);
	if (!s)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnv(info, "HOME=");
		if (!dir)
			chdirRet = /* TODO: what should this be? */
				chdir((dir = getEnv(info, "PWD=")) ? dir : "/");
		else
			chdirRet = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getEnv(info, "OLDPWD="))
		{
			puts(s);
			putchar('\n');
			return (1);
		}
		puts(getEnv(info, "OLDPWD=")), putchar('\n');
		chdirRet = /* TODO: what supposed this be? */
			chdir((dir = getEnv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirRet = chdir(info->argv[1]);
	if (chdirRet == -1)
	{
		printError(info, "can't cd to ");
		ePuts(info->argv[1]), ePutchar('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", getEnv(info, "PWD="));
		setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myHelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*argArray); /* temp att_unused workaround */
	return (0);
}
