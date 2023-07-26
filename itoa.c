#include "main.h"

/**
 * _reverse - reverses a string in place
 * @str: the string to reverse
 * @length: number of bytes to reverse
 */
void _reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;
	char temp;

	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

/**
 * _itoa - convert int to string
 * @num: the number to convert
 * @str: where to store the output string
 * @base: the input number base
 * Return: the resulting string
 */
char *_itoa(int num, char str[], int base)
{
	int i = 0, rem;

	if (base < 2 || base > 36)
	{
		str[0] = '\0';
		return (str);
	}

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}

	while (num != 0)
	{
		rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	str[i] = '\0';

	_reverse(str, i);

	return (str);
}
