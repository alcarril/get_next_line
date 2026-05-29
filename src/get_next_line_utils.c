/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:22:43 by alex              #+#    #+#             */
/*   Updated: 2024/12/08 01:38:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	***create_tree_branches(void ***tree, int fd)
{
	int	t;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!tree)
	{
		t = 0;
		tree = (void ***)malloc(sizeof(void **) * (MAX_FD + 4));
		if (!tree)
			return (NULL);
		while (t < (MAX_FD + 4))
		{
			tree[t] = NULL;
			++t;
		}
	}
	if (!tree[fd] && tree && fd >= 0)
	{
		tree[fd] = create_new_branch(tree, fd);
		if (!tree)
			return (NULL);
	}
	return (tree);
}

void	**create_new_branch(void ***tree, int fd)
{
	ssize_t	i;
	ssize_t	line;

	i = 0;
	line = 0;
	tree[fd] = (void **)malloc(sizeof(void *) * 5);
	if (!tree[fd])
		return (NULL);
	while (i < 5)
	{
		tree[fd][i] = NULL;
		i++;
	}
	while (line <= 2)
	{
		tree[fd][line] = (void *)malloc(sizeof(ssize_t) * 2);
		if (!tree[fd][line])
			return (NULL);
		((ssize_t *)tree[fd][line])[0] = 0;
		((ssize_t *)tree[fd][line])[1] = 0;
		line++;
	}
	return (tree[fd]);
}

void	**ft_redim_fill_table(void **table, ssize_t new_lines, ssize_t lines)
{
	void	**aux_fill_table;
	int		i;

	if (lines >= new_lines)
		return (table);
	new_lines = new_lines + 1;
	aux_fill_table = (void **)malloc(sizeof(void *) * (new_lines + 4));
	if (!aux_fill_table)
		return (NULL);
	aux_fill_table[new_lines + 4 - 1] = NULL;
	table[0] = ft_realloc_fill_ssline(table, new_lines, lines, 0);
	if (!table[0])
		return (free(aux_fill_table), NULL);
	((ssize_t *)table[2])[0] = new_lines - 1;
	i = -1;
	while (++i <= (lines + 4))
	{
		aux_fill_table[i] = table[i];
	}
	free(table);
	table = aux_fill_table;
	return (table);
}

void	*ft_realloc_fill_ssline(void **table, ssize_t new_columns,
		ssize_t columns, ssize_t target)
{
	void	*aux_fill_size_l;
	ssize_t	i;

	i = 0;
	aux_fill_size_l = (void *)malloc(sizeof(ssize_t) * (new_columns + 1));
	if (!aux_fill_size_l)
		return (NULL);
	((ssize_t *)aux_fill_size_l)[new_columns] = 0;
	while (i <= (columns + 1))
	{
		((ssize_t *)aux_fill_size_l)[i] = ((ssize_t *)table[0])[i];
		i++;
	}
	free(table[target]);
	table[target] = aux_fill_size_l;
	return (table[target]);
}

void	***free_all(void ***tree, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tree)
	{
		while (i <= 2 || tree[i] != NULL)
		{
			if (tree[i])
			{
				while (tree[i][j] != NULL)
				{
					free(tree[i][j]);
					j++;
				}
				free(tree[i]);
			}
			j = 0;
			i++;
		}
	}
	if (buffer)
		free(buffer);
	return (free(tree), NULL);
}
