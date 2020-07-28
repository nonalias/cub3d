/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:34:42 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:33:11 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

static void	insert_map2(t_mlx *mlx, char *str, int i, int j)
{
	if (str[j] == ' ')
		mlx->map[i][j] = -1;
	else if (str[j] >= '0' && str[j] <= '4')
		mlx->map[i][j] = str[j] - '0';
	else if (str[j] == 'N' || str[j] == 'S' || str[j] == 'W' || str[j] == 'E')
	{
		if (mlx->dir != 0)
			display_error("invalid map(too many pos)");
		else
		{
			mlx->dir = str[j];
			mlx->map[i][j] = 0;
			mlx->player.x = (j * 64) + 32;
			mlx->player.y = (i * 64) + 32;
		}
	}
	else
		display_error("invalid map");
}

static void	insert_map(t_mlx *mlx, char *str, int i)
{
	int	j;
	int	str_size;

	if (i == mlx->map_h)
		return ;
	str_size = ft_strlen(str);
	j = -1;
	while (++j < mlx->map_w)
	{
		if (j < str_size)
			insert_map2(mlx, str, i, j);
		else
			mlx->map[i][j] = -1;
	}
}

int			array_parse_2(t_mlx *mlx, char *str, int *flag)
{
	static int	i;

	if ((ft_isdigit(str[0]) || str[0] == ' ') && *flag == 2)
	{
		if (!(mlx->map = (int**)malloc((mlx->map_h) * sizeof(int*))))
			return (display_error("malloc error"));
		*flag = 3;
	}
	if (*flag == 2 || str[0] == '\0')
	{
		free(str);
		return (0);
	}
	if (!(mlx->map[i++] = (int*)malloc((mlx->map_w) * sizeof(int))))
		return (display_error("malloc error"));
	insert_map(mlx, str, i - 1);
	free(str);
	return (0);
}
