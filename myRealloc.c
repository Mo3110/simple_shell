#include "shell.h"

/**
 * *myMemset - fills memory with a constant byte
 * @pt: the pointer to the memory area
 * @value: the byte to fill *pt with
 * @size: the amount of bytes to be filled
 *
 * Return: a pointer to the memory area pt
 */
char *myMemset(char *pt, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		pt[i] = value;
	return (pt);
}

/**
 * ffree - frees a string of strings
 * @strings: string of strings
 */
void ffree(char **strings)
{
	char **temp = strings;

	if (!strings)
		return;
	while (*strings)
		free(*strings++);
	free(temp);
}

/**
 * *myRealloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ed block
 * @oldSize: byte size of previous block
 * @newSize: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *myRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);
	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);
	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (newPtr);
}
