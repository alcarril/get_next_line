/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1pathargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:19:10 by alex              #+#    #+#             */
/*   Updated: 2024/11/18 22:05:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void    ft_putstr_fd(char *s, int fd)
{
        while (*s)
        {
                write(fd, s, 1);
                s++;
        }
}

size_t  ft_strlen1(const char *s)
{
        size_t  n;

        n = 0;
        while (*s)
        {
                n++;
                s++;
        }
        return (n);
}


char    *ft_strjoin1(char const *s1, char const *s2)
{
        char    *ptr;
        size_t  total_len;
        size_t  i;
        size_t  j;

        if (!s1 || !s2)
                return (NULL);
        j = 0;
        i = 0;
        total_len = ft_strlen1(s1) + ft_strlen1(s2) + 1;
        ptr = (char *)malloc(total_len);
        if (!ptr)
                return (NULL);
        while ((i <= (total_len - 1)) && s1[i] != '\0')
        {
                ptr[i] = s1[i];
                i++;
        }
        while ((i < (total_len - 1)) && s2[j] != '\0')
                ptr[i++] = s2[j++];
        ptr[i] = '\0';
        return (ptr);
}

int main(int argz, char **argv)
{
    static char *line; //lo crea como estaticoo para inicilizarlo a null
    char bool;
    int  fd;
    char *name;
    char *file;
    char path[] = "/home/alex/GNL/GNL_imputs/";

    name = argv[1];    
    file = ft_strjoin1(path, name);
    bool = 0;
    if (!argz)
            return(0);
    fd = open(file, O_RDONLY);
    printf("el valor del fd es: %d\n\n\n", fd);
    if (fd == 0)//porque hay que poner esto
    {
        return(0);
    }
    while (!bool || line != NULL)// es lo mismo que poner while s??
    {
        bool = 1;
        line = get_next_line(fd);
        ft_putstr_fd(line, 0);//depende de si necesitamos meter le salto de linea a mano o no, en teoria no hace falta.
    }
        close(fd);
    return(0);
}

