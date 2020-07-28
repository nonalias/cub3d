/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 19:30:50 by dochoi            #+#    #+#             */
/*   Updated: 2020/04/03 21:32:24 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	buf_to_table(char *buf, long size,
		int *flag, t_string *fd_table)
{
	long	i;

	if (fd_table->str != 0)
	{
		free(fd_table->str);
		fd_table->str = 0;
	}
	i = 0;
	*flag = 1;
	if (!(fd_table->str = malloc((unsigned int)size)))
	{
		*flag = 0;
		return ;
	}
	while (i < size)
	{
		fd_table->str[i] = buf[i];
		i++;
	}
	fd_table->size = size;
}

static void	buf_to_table_connect(char *buf,
		long size, int *flag, t_string *fd_table)
{
	long	i;
	char	*temp;
	long	j;

	j = 0;
	i = 0;
	*flag = 1;
	if (!(temp = malloc((unsigned int)(size + fd_table->size))))
	{
		*flag = 0;
		return ;
	}
	while (i < fd_table->size)
	{
		temp[i] = fd_table->str[i];
		i++;
	}
	while (i < fd_table->size + size)
		temp[i++] = buf[j++];
	free(fd_table->str);
	fd_table->str = temp;
	fd_table->size += size;
}

static void	ft_set_line(t_string *fd_table, int n_idx)
{
	long	i;
	long	j;

	j = 0;
	i = n_idx + 1;
	while (i < fd_table->size)
	{
		fd_table->str[j] = fd_table->str[i];
		i++;
		j++;
	}
	fd_table->size -= (n_idx + 1);
}

static int	ft_str_to_line(char **line, t_string *fd_table, char *buf)
{
	long	i;
	long	n_idx;

	n_idx = ft_str_in_enter(fd_table);
	if (!(*line = malloc(n_idx + 1)))
		return (-1);
	i = 0;
	while (i < n_idx)
	{
		(*line)[i] = fd_table->str[i];
		i++;
	}
	(*line)[i] = '\0';
	ft_set_line(fd_table, n_idx);
	free(buf);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_string	fd_table[MAX_FD_SIZE];
	long			ret;
	char			*buf;
	int				flag;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0 || !(buf = malloc(BUFFER_SIZE)))
		return (-1);
	if (ft_str_in_enter(&fd_table[fd]) != -1)
		return (ft_str_to_line(line, &fd_table[fd], buf));
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		fd_table[fd].size == 0 ? buf_to_table(buf, ret, &flag, &fd_table[fd]) :
			buf_to_table_connect(buf, ret, &flag, &fd_table[fd]);
		if (!flag)
			ft_free_buf(buf);
		if (ft_str_in_enter(&fd_table[fd]) != -1)
			return (ft_str_to_line(line, &fd_table[fd], buf));
	}
	if (ret == 0)
		return (ft_reached_eof(line, &fd_table[fd], buf));
	return (ft_free_buf(buf));
}
