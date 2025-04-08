#include "libft.h"

char    *ft_strcpy(char *s2, char *s1)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!*s1)
        return (NULL);
    while (s1[i])
    {
        s2[j] = s1[i];
        i++;
        j++;
    }
    s2[j] = '\0';
    return (s2);
}