#include "main.h"
/**
 * _strcspn - calculates the length of the
 *      initial segment of a string that consists
 *      entirely of characters in another string
 * @s: the string
 * @reject: second argument
 * Return: the position if a matching character is
 *      found in reject or the length of the
 *      string if none is found
 */

unsigned int _strcspn(char *s, char *reject)
{
        unsigned int i, j;

        for (i = 0; s[i] != '\0'; i++)
        {
                for (j = 0; reject[j] != '\0'; j++)
                {
                        if (reject[j] == s[i])
                                return (i);
                }
        }
        return (i);
}

