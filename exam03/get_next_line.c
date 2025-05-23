
#include "get_next_line.h"

char *ft_strdup(char *src)
{
    char *dest;
    int i = 0;

    while(src[i])
        i++;
    dest = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *get_next_line(int fd)
{
    static char buff[BUFFER_SIZE];
    char li[70000];
    static int b_r;
    static int b_p;
    int i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (b_p >= b_r)
        {
            b_r = read(fd, buff, BUFFER_SIZE);
            b_p = 0;
            if (b_r <= 0)
                break ;
        }
        li[i++] = buff[b_p++];
        if (buff[b_p] == '\n')
            break ;
    }
    li[i] = '\0';
    if (i == 0)
        return (NULL);
    return(ft_strdup(li));
}
