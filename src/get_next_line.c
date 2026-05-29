/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:08:35 by alex              #+#    #+#             */
/*   Updated: 2026/05/29 07:24:37 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Returns the next line read from fd.
 * @param fd File descriptor to read from.
 * @return Line including '\n', or NULL on EOF/error.
 */
char	*get_next_line(int fd)
{
	static void	***tree;
	char		*buffer;

	buffer = NULL;
	tree = create_tree_branches(tree, fd);
	if (!tree)
	{
		tree = free_all(tree, buffer);
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
	{
		tree = free_all(tree, buffer);
		return (NULL);
	}
	tree = read_imput_controler(tree, buffer, fd);
	if (!tree || !tree[fd] || !tree[fd][3])
	{
		tree = free_all(tree, buffer);
		return (NULL);
	}
	return (free(buffer), (char *)tree[fd][3]);
}

/**
 * @brief Fills the table until a full line is available.
 * @param tree Main cache.
 * @param buffer Read buffer.
 * @param fd File descriptor.
 * @return Updated tree, or NULL on allocation failure.
 */
void	***read_imput_controler(void ***tree, char *buffer, int fd)
{
	ssize_t	readed;
	ssize_t	len_out_line;

	if (tree[fd][3] != NULL)
		tree = dispatch_table_lines(tree, fd);
	len_out_line = ((ssize_t *)tree[fd][0])[0];
	while (!tree[fd][3] || ((char *)tree[fd][3])[len_out_line - 1] != '\n')
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
		{
			break ;
		}
		tree[fd] = ft_split_lines(tree[fd], buffer, readed);
		if (!tree[fd] || !tree[fd][3])
			return (NULL);
		len_out_line = ((ssize_t *)tree[fd][0])[0];
	}
	return (tree);
}

/**
 * @brief Splits buffer into line chunks and appends to table.
 * @param ta Table.
 * @param s Buffer.
 * @param readed Bytes read.
 * @return Updated table, or NULL on allocation failure.
 */
void	**ft_split_lines(void **ta, char *s, ssize_t readed)
{
	ssize_t	i;
	ssize_t	b;
	ssize_t	e;
	ssize_t	cl;

	i = -1;
	cl = -1;
	while (++i < readed && readed != 0)
	{
		if (i == 0 || (i >= 1 && s[i - 1] == '\n'))
			b = i;
		if (i == (readed - 1) || s[i] == '\n')
		{
			e = i;
			ta = ft_redim_fill_table(ta, ++cl, ((ssize_t *)ta[2])[0]);
			if (!ta)
				return (NULL);
			ta[cl + 3] = l(((char *)ta[cl + 3]), &s[b], ((ssize_t *)ta[0])[cl],
					(e - b + 1));
			if (!ta[cl + 3])
				return (NULL);
			((ssize_t *)ta[0])[cl] = (e - b + 1) + ((ssize_t *)ta[0])[cl];
		}
	}
	return (ta);
}

/**
 * @brief Joins existing line with a bounded buffer slice.
 * @param line Current line.
 * @param buffer Source buffer.
 * @param len Current line length.
 * @param cut Bytes to append.
 * @return New line string, or NULL on allocation failure.
 */
char	*l(char *line, char *buffer, ssize_t len, ssize_t cut)
{
	char	*ptr;
	void	*aux_line;
	ssize_t	total_len;
	ssize_t	i;
	ssize_t	j;

	aux_line = line;
	total_len = len + cut;
	if (total_len == 0)
		return (NULL);
	ptr = (char *)malloc(total_len + 1);
	if (!ptr)
		return (NULL);
	j = 0;
	i = -1;
	while ((++i <= (total_len - 1)) && i < len)
		ptr[i] = line[i];
	while ((i <= (total_len - 1)) && j <= cut)
		ptr[i++] = buffer[j++];
	ptr[i] = '\0';
	free(aux_line);
	return (ptr);
}

/**
 * @brief Shifts stored lines so the next pending line is first.
 * @param tree Main cache.
 * @param fd File descriptor index.
 * @return Updated tree.
 */
void	***dispatch_table_lines(void ***tree, int fd)
{
	ssize_t	i;

	i = -1;
	while (tree[fd][++i + 3] != NULL)
	{
		tree[fd][i + 3] = tree[fd][i + 3 + 1];
		((ssize_t *)tree[fd][0])[i] = ((ssize_t *)tree[fd][0])[i + 1];
	}
	return (tree);
}
