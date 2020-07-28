/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:14:49 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 17:03:12 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

void		map_init(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->win_w = 1024;
	mlx->win_h = 512;
	mlx->no_wall.size_l = 0;
	mlx->so_wall.size_l = 0;
	mlx->we_wall.size_l = 0;
	mlx->ea_wall.size_l = 0;
	mlx->sp.size_l = 0;
	mlx->c_color = DEFAULT_CEILING_COLOR;
	mlx->f_color = DEFAULT_FLOOR_COLOR;
	mlx->map = 0;
	mlx->map_w = 0;
	mlx->map_h = 0;
	mlx->dir = 0;
	mlx->save_flag = 0;
	ft_memset(mlx->key_check, 0, sizeof(mlx->key_check));
	while (++i < 8)
		mlx->flag_check[i] = 0;
}

static int	what_identifier_go(char **strs, t_mlx *mlx)
{
	if (!ft_strncmp("R", strs[0], 1))
		what_flag_r(strs, mlx);
	else if (!ft_strncmp("NO", strs[0], 2))
		what_flag_no(strs, mlx);
	else if (!ft_strncmp("SO", strs[0], 2))
		what_flag_so(strs, mlx);
	else if (!ft_strncmp("WE", strs[0], 2))
		what_flag_we(strs, mlx);
	else if (!ft_strncmp("EA", strs[0], 2))
		what_flag_ea(strs, mlx);
	else if (!ft_strncmp("S", strs[0], 1))
		what_flag_s(strs, mlx);
	else if (!ft_strncmp("F", strs[0], 1))
		what_flag_f(strs, mlx);
	else if (!ft_strncmp("C", strs[0], 1))
		what_flag_c(strs, mlx);
	else
		return (-1);
	return (0);
}

static int	line_parse(t_mlx *mlx, char *str, int *flag)
{
	char	**strs;
	int		i;

	if (!(ft_strncmp("", str, 1)))
	{
		free(str);
		return (0);
	}
	while (*str && *str == ' ')
		str++;
	if (!(strs = ft_split(str, ' ')) || *strs == 0)
		return (display_error("malloc error"));
	i = 0;
	if (*flag == 0)
		if (what_identifier_go(strs, mlx) == -1)
			return (display_error("flag error."));
	*flag = 1;
	while (i < 8)
		if (mlx->flag_check[i++] == 0)
			*flag = 0;
	split_free(strs);
	free(str);
	return (0);
}

static int	array_parse(t_mlx *mlx, char *str, int *flag)
{
	int			map_width;

	if (!(ft_strncmp("", str, 1)))
	{
		free(str);
		if (*flag == 2)
			return (display_error("invalid map"));
		return (0);
	}
	else
		*flag = 2;
	mlx->map_h += 1;
	map_width = ft_strlen(str);
	if (mlx->map_w < map_width)
		mlx->map_w = map_width;
	free(str);
	return (0);
}

int			map_parse(t_mlx *mlx, char *filename)
{
	char	*str;
	int		fd;
	int		ret;
	int		flag;

	fd = open(filename, O_RDONLY);
	flag = 0;
	while ((ret = get_next_line(fd, &str)) > 0)
		if (!flag)
			line_parse(mlx, str, &flag);
		else
			array_parse(mlx, str, &flag);
	close(fd);
	fd = open(filename, O_RDONLY);
	while ((ret = get_next_line(fd, &str)) > 0)
		array_parse_2(mlx, str, &flag);
	if (ret == -1)
		return (display_error("invalid map"));
	close(fd);
	return (0);
}
