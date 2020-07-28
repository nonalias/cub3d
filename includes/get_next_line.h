/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 21:23:32 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/06 16:24:47 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define MAX_FD_SIZE 1024
# define BUFFER_SIZE 1024

typedef struct	s_string
{
	char			*str;
	long			size;
}				t_string;

int				ft_reached_eof(char **line, t_string *fd_table, char *buf);
int				ft_free_buf(char *buf);
int				ft_str_in_enter(t_string *fd_table);
int				get_next_line(int fd, char **line);

#endif
