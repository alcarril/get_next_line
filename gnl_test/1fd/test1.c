/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:42:25 by alex              #+#    #+#             */
/*   Updated: 2024/11/28 20:50:35 by alex             ###   ########.fr       */
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
int main(void)
{
    int fd;
    static char *line; //lo crea como estaticoo para inicilizarlo a null 
    char bool;
    
    bool = 0;
    fd = 2;
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
            printf("nulo");
            return (0);
        }
        ft_putstr_fd(line, 0);//depende de si necesitamos meter le salto de linea a mano o no, en teoria no hace falta.
    }
	close(fd);
    return(0);
}
