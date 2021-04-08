#include "shell.h"
/**
 * _strcat - Concatenates two strings..
 * @dest: The first pointer.
 * @src: The second pointer
 *
 * Return: To the value of dest.
 */
char *_strcat(char *dest, char *src)
{
int i = 0;
int j = 0;
while (dest[i] != '\0')
{
i++;
}
while (src[j] != '\0')
{
dest[i + j] = src[j];
j++;
}
dest[i + j] = '\0';
return (dest);
}
/**
* _strcmp - Compares two strings.
* @s1: The first char.
* @s2: The second char.
*
* Return: To the value of int.
*/
int _strcmp(char *s1, char *s2)
{
int n = 0;
int i = 0;
for (i = 0; (s1[i] != '\0' || s2[i] != '\0'); i++)
{
if (s1[i] != s2[i])
{
n = s1[i] - s2[i];
break;
}
}
return (n);
}
/**
* free_double - Free the grid
* @ptr: Double pointer.
*
*/
void free_double(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
/**
 * *_strcpy -  copies the string pointed to by src.
 * @dest: The first pointer.
 * @src: The second pointer
 * Return: To the value of char.
 */
char *_strcpy(char *dest, char *src)
{
int i;
i = 0;
while (src[i] != 0)
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
/**
* _strlen - Returns the length of a string.
* @s: The pointer.
*
* Return: To the value of s.
*/
int _strlen(char *s)
{
int cont;
int i;
i = 0;
cont = 0;
while (s[i] != 0)
{
i++;
}
cont = cont + i;
return (cont);
}
/**
* _strtok - tokenized
* @str: var type string
* @limi: delimitator
* Return: Var type char *
*/
char *_strtok(char *str, char *limi)
{
	int i;
	static char *s;

	if (!str)
		str = s;
	i = *str++;
	while (_strchr(limi, i))
	{
		if (i == 0)
			return (0);
		i = *str++;
	}
	--str;
	s = str + _strcspn(str, limi);
	if (*s != 0)
	{
		*s = 0;
		s++;
	}
	return (str);
}
/**
 * _strchr - locates character
 * @stri: var type char *
 * @car: var type char
 * Return: pointer to the first occurrence of the character
 */
char *_strchr(char *stri, char car)
{
	while (*stri != 0)
	{
		if (*stri == car)
			return (stri);
		stri++;
	}
	if (*stri == car)
		return (stri);
	return (0);
}

/**
 * _strcspn - The length
 * @str: Var type char *
 * @pre: prefix string
 * Return: Unsigned int
 */
unsigned int _strcspn(char *str, char *pre)
{
	unsigned int len = 0, i = 0;

	while (str[len] != 0)
	{
		int flag = 0;

		for (i = 0; pre[i] != 0; i++)
		{
			if (str[len] == pre[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			len++;
		else
			break;
	}
	return (len);
}
