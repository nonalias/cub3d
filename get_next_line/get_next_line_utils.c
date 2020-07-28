/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 15:05:36 by dochoi            #+#    #+#             */
/*   Updated: 2020/04/03 21:27:11 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_str_in_enter(t_string *fd_table)
{
	long	i;

	i = 0;
	while (i < fd_table->size)
	{
		if (fd_table->str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_free_buf(char *buf)
{
	free(buf);
	return (-1);
}

int	ft_reached_eof(char **line, t_string *fd_table, char *buf)
{
	long	i;

	i = 0;
	if (!((*line) = malloc((unsigned int)(fd_table->size + 1))))
		return (-1);
	while (i < fd_table->size)
	{
		(*line)[i] = fd_table->str[i];
		i++;
	}
	(*line)[i] = '\0';
	if (fd_table->str != 0)
	{
		free(fd_table->str);
		fd_table->str = 0;
	}
	fd_table->size = 0;
	free(buf);
	return (0);
}
