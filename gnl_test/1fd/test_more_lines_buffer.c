/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_more_lines_buffer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:39:26 by alex              #+#    #+#             */
/*   Updated: 2024/11/21 21:13:52 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int     ft_atoi(const char *nptr)
{
        int     sing;
        int     num;

        sing = 1;
        num = 0;
        while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
        {
                nptr++;
        }
        if (*nptr == '-' || *nptr == '+')
        {
                if (*nptr == '-')
                {
                        sing = -1;
                }
                nptr++;
        }
        while (*nptr >= '0' && *nptr <= '9')
        {
                num = num * 10 + (*nptr - '0');
                nptr++;
        }
        return (num * sing);
}

void    write_more_lines(int fd, unsigned long reps)
{
    unsigned long   max_bytes;
    unsigned long   chars;
    unsigned long   lines;
    unsigned long   i;
    
    max_bytes = 0;
    chars = reps + 1;
    lines = 0;
    i = 0;
    while(--reps && chars > 0)//reps es numero de veces que se repite el proceso
    {
        while(chars != 0 && max_bytes < BUFFER_SIZE)
        {
            write(fd, "a", 1);
            chars--;
            max_bytes++;
        }
        while(lines < BUFFER_SIZE && max_bytes < BUFFER_SIZE)
        {
            write(fd, "\n", 1);
            lines++;
            max_bytes++;
        }
        max_bytes = 0;
        i++;
        chars = reps - i;
        lines =  i;
    }
    printf("se ha repetido %ld veces la operacion, para un BUFFER de: %d bytes", reps, BUFFER_SIZE);
}
int main(int argc, char **argv)
{
    unsigned long   reps;
    int             fd;
    static char *line; //lo crea como estaticoo para inicilizarlo a null
    char bool;

    if (argc < 1)
        return (0);
    reps = BUFFER_SIZE;//puedo castear aqui directamente o tengo que usar intermediario
    fd =  open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
    write_more_lines(fd, reps);
    close (fd);
    
    printf("\n\n\n########################se ha escrito el documento####################################\n\n\n");

    fd =  open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0666);//o usar lseek para vlver a poner el puntero en cero 
    bool = 0;
    printf("el valor del fd es: %d\n\n\n", fd);
    if (fd == 0)//porque hay que poner esto
    {
        return(0);
    }   
    while (!bool || line != NULL)// es lo mismo que poner while s??
    {
        bool = 1;
        line = get_next_line(fd);
        if (!line)
        {
            printf("la direcion de la linea es %p", line);
            close(fd);
            break ;
        }
        printf("%s", line);//depende de si necesitamos meter le salto de linea a mano o no, en teoria no hace falta.
    }
    close(fd);
    return(0);
}

