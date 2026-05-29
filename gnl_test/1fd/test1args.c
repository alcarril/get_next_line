/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:42:25 by alex              #+#    #+#             */
/*   Updated: 2024/11/30 12:40:32 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
//el main tiene que incluir el salto de linea ??
int main(int argz, char **argv)
{
    int fd;
    static char *line; //lo crea como estaticoo para inicilizarlo a null 
    char bool;
    int i = 0;
    
    bool = 0;
    if (!argz)
	    return(0);
    fd = open(argv[1], O_RDONLY);
    printf("el valor del fd es: %d\n\n\n", fd);
    if (fd == 0)//porque hay que poner esto 
    {
        return(0);
    }
    while (!bool || line != NULL)// es lo mismo que poner while s??
    {
        bool = 1;
        line = get_next_line(fd);
        printf("linea numero: %d\n\n\n", i);
	    if (!line)
	    {
		    printf("la direccio de line es %p\n", line);
		    break;
	    }
        ft_putstr_fd(line, 0);//depende de si necesitamos meter le salto de linea a mano o no, en teoria no hace falta.
        i++;
    }
	close(fd);
    return(0);
}
