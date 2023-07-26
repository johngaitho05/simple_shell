#include "main.h"

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to the resulting string
 */
char *_strcpy(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (original_dest);
}

/**
 * _atoi- convert string to int
 * @str: the string to convert
 * Return: the converted number
 */
int _atoi(char *str)
{
	int num = 0, i;
	char *allowed_chars = "0123456789";

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!_strchr(allowed_chars, str[i]))
		{
			num = -1;
			break;
		}
		num = num * 10 + (str[i] - 48);
	}
	return (num);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strlen - Returns the length of a string
 * @s: Pointer to the string to be measured
 *
 * Return: The length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}

/**
 * _strncat - concatenates two strings
 * @s1: the first string
 * @s2: the second string
 * Return: s1 + s2
 */
char *_strncat(char *s1, char *s2)
{
	int i = 0, j = 0, length = _strlen(s1) + _strlen(s2);
	char *res = malloc(sizeof(char) * length);

	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
