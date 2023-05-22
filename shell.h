#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a
 * function, allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of string generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on counts this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of a pointer to cmd_buf,on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0,\
       	NULL, 0, 0, 0}

/**
 * struct builtn - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtn
{
	char *type;
	int (*func)(info_t*);
} builtin_table;


/* toem_myShelloop.c */
int myShellLopp(info_t *, char **);
int findBuiltin(info_t *);
void findCmd(info_t *);
void forkCmd(info_t *);

/* toem_doParser.c */
int isCmd(info_t *, char *);
char *dupChars(char *, int, int);
char *findPath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* ok_errors.c */
void ok_eputs(char *);
int ok_eputchar(char);
int ok_putfd(char o, int fd);
int ok_putsfd(char *str, int fd);

/* toem_stringManipulation.c */
int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *stringConcatenate(char *, char *);

/* toem_stringManipulation1.c */
char *stringCopy(char *, char *);
char *stringDuplicate(const char *);
void printString(char *);
int printCharacter(char);

/* toem_exitts.c */
char *strnCpy(char *, char *, int);
char *strnCat(char *,char *, int);
char *strChr(char *, char);

/* toem_tokenize.c */
char **strTow(char *, char *);
char **strTow2(char *, char);

/* toem_myRealloc.c */
char *myMemset(char *, char, unsigned int);
void ffree(char **);
void *myRealloc(void *, unsigned int, unsigned int);

/* toem_memori.c */
int ofree(void **);

/* toem_strtoint.c */
int isInteractiveMode(info_t *);
int isDelimiter(char, char *);
int isAlphaCharacter(int);
int stringToInteger(char *);

/* toem_errrs1.c */
int errAtoi(char *);
void printError(info_t *, char *);
int printD(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);

/* toem_builtn.c */
int myExit(info_t *);
int myCd(info_t *);
int myHelp(info_t *);

/* toem_builtn1.c */
int myHistory(info_t *);
int myAlias(info_t *);

/* toem_getLineInShl.c */
ssize_t getInput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinf.c */
void clearInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);

/* toem_enviro.c */
char *_getEnv(info_t *, const char *);
int myEnv(info_t *);
int mySetEnv(info_t *);
int myUnsetenv(info_t *);
int populateEnvList(info_t *);

/* toem_getenviro.c */
char **getEnviron(info_t *);
int unsetEnv(info_t *, char *);
int setEnv(info_t *, char *, char *);

/* toem_gethistory.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryLlist(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* toem_linkedlist.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
size_t printListStr(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* toem_linkedlist1.c */
size_t listLen(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* toem_vars.c */
int isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVars(info_t *);
int replaceString(char **, char *);

#endif
