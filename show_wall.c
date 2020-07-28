/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:47:09 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 13:51:50 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

static void	show_wall5(t_mlx *mlx)
{
	if (!mlx->ray.v_close_flag)
	{
		if (mlx->ray.h_so_flag)
			mlx->color = mlx->so_wall.data[mlx->ray.map_dochoi_y
			* 64 + mlx->ray.temp];
		else
			mlx->color = mlx->no_wall.data[mlx->ray.map_dochoi_y
			* 64 + mlx->ray.temp];
	}
	else
	{
		if (mlx->ray.v_ea_flag)
			mlx->color = mlx->ea_wall.data[mlx->ray.map_dochoi_y
			* 64 + mlx->ray.temp];
		else
			mlx->color = mlx->we_wall.data[mlx->ray.map_dochoi_y
			* 64 + mlx->ray.temp];
	}
	set_dark(mlx, mlx->ray.dist);
}

static void	show_wall4(t_mlx *mlx)
{
	mlx->ray.count_w = mlx->ray.r;
	mlx->ray.idx = (mlx->ray.count_h + (int)(mlx->ray.line_o)) * (mlx->win_w)
	+ mlx->ray.count_w;
	if (!(mlx->ray.idx < mlx->win_w * mlx->win_h && mlx->ray.idx >= 0))
		return ;
	mlx->ray.map_dochoi_y = (int)((((float)(mlx->ray.count_h) +
	((mlx->ray.temp2 - mlx->ray.line_h) / 2)) / mlx->ray.temp2) * 64);
	if (mlx->ray.map_dochoi_y < 0)
		mlx->ray.map_dochoi_y = 0;
	mlx->ray.temp = lround(mlx->ray.map_dochoi_x);
	if (mlx->ray.temp < 0)
		mlx->ray.temp = 0;
	if (mlx->ray.temp >= 64)
		mlx->ray.temp = 63;
	show_wall5(mlx);
	mlx->img.data[mlx->ray.idx] = mlx->color;
}

static void	show_wall3(t_mlx *mlx)
{
	while (++(mlx->ray.count_h) < (int)(mlx->ray.line_h))
		show_wall4(mlx);
}

static void	show_wall2(t_mlx *mlx)
{
	mlx->ray.ca = mlx->player.angle - mlx->ray.ra;
	if (mlx->ray.ca < 0)
		mlx->ray.ca += 2 * M_PI;
	if (mlx->ray.ca > 2 * M_PI)
		mlx->ray.ca -= 2 * M_PI;
	mlx->ray.dist = mlx->ray.dist * cos(mlx->ray.ca);
	mlx->ray.line_h = (64 * mlx->win_h) / mlx->ray.dist;
	mlx->ray.temp2 = mlx->ray.line_h;
	mlx->ray.count_h = -1;
	if (mlx->ray.line_h >= mlx->win_h)
	{
		mlx->ray.count_h -= (mlx->ray.line_h - mlx->win_h);
		if (mlx->ray.count_h < -1000)
			mlx->ray.count_h = -1000;
		mlx->ray.line_h = mlx->win_h - 1;
	}
	mlx->ray.line_o = (mlx->win_h / 2) - mlx->ray.line_h / 2
	+ mlx->player.jump_cnt;
	if (mlx->ray.line_o < 0)
		mlx->ray.line_o = 0;
	show_wall3(mlx);
}

void		show_wall(t_mlx *mlx)
{
	mlx->color = 0;
	if (mlx->ray.dist_v < mlx->ray.dist_h)
	{
		mlx->ray.map_dochoi_x = mlx->ray.map_dochoi_x2;
		mlx->ray.rx = mlx->ray.vx;
		mlx->ray.ry = mlx->ray.vy;
		mlx->ray.dist = mlx->ray.dist_v;
		mlx->ray.v_close_flag = 1;
	}
	if (mlx->ray.dist_h < mlx->ray.dist_v)
	{
		mlx->ray.dist = mlx->ray.dist_h;
		mlx->ray.rx = mlx->ray.hx;
		mlx->ray.ry = mlx->ray.hy;
		mlx->ray.v_close_flag = 0;
	}
	mlx->ray.ra += mlx->ray.dr_dochoi;
	if (mlx->ray.ra < 0)
		mlx->ray.ra += 2 * M_PI;
	else if (mlx->ray.ra > 2 * M_PI)
		mlx->ray.ra -= 2 * M_PI;
	show_wall2(mlx);
}
