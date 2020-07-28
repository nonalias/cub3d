/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:46:10 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 17:02:55 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

int	g_dx[4];
int	g_dy[4];

static void		d_init(void)
{
	g_dx[0] = 1;
	g_dy[0] = 0;
	g_dx[1] = 0;
	g_dy[1] = 1;
	g_dx[2] = -1;
	g_dy[2] = 0;
	g_dx[3] = 0;
	g_dy[3] = -1;
}

static void		find_map(t_mlx *mlx, int bi, int bj, int **check)
{
	int	i;
	int	nx;
	int	ny;

	i = -1;
	while (++i < 4)
	{
		nx = bj + g_dx[i];
		ny = bi + g_dy[i];
		if (nx >= 0 && nx < mlx->map_w && ny >= 0 && ny < mlx->map_h)
		{
			if (check[ny][nx] != 1)
			{
				check[ny][nx] = 1;
				if (mlx->map[ny][nx] == -1)
					display_error("invalid map");
				else if (mlx->map[ny][nx] == 0)
					find_map(mlx, ny, nx, check);
				if (nx == 0 || ny == 0 || nx == mlx->map_w - 1
				|| ny == mlx->map_h - 1)
					if (mlx->map[ny][nx] != 1)
						display_error("invalid map");
			}
		}
	}
}

static int		**make_check(t_mlx *mlx, int **check)
{
	int	i;
	int	j;

	i = -1;
	if (!(check = (int**)malloc(sizeof(int*) * mlx->map_h)))
		display_error("malloc error");
	while (++i < mlx->map_h)
	{
		if (!(check[i] = (int*)malloc(sizeof(int) * mlx->map_w)))
			display_error("malloc error");
		j = -1;
		while (++j < mlx->map_w)
			check[i][j] = 0;
	}
	return (check);
}

void			map_check(t_mlx *mlx)
{
	int	i;
	int	j;
	int	**check;

	check = 0;
	check = make_check(mlx, check);
	d_init();
	if (mlx->map == 0)
		display_error("invalid map");
	i = -1;
	while (++i < mlx->map_h)
	{
		j = -1;
		while (++j < mlx->map_w)
		{
			if (mlx->map[i][j] == 0 && check[i][j] == 0)
				find_map(mlx, i, j, check);
		}
	}
}
