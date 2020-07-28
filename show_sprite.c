/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 21:47:07 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 18:25:25 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

void	show_sprite4(t_mlx *mlx)
{
	if (mlx->ray.map_dochoi_x2 < 0)
		mlx->ray.map_dochoi_x2 = 0;
	if (mlx->ray.map_dochoi_x2 >= 64)
		mlx->ray.map_dochoi_x2 = 63;
	if (mlx->ray.sp_list->type == 2)
		mlx->color = mlx->sp.data[mlx->ray.map_dochoi_y * 64
		+ (int)(mlx->ray.map_dochoi_x2)];
	else if (mlx->ray.sp_list->type == 3)
		mlx->color = mlx->ani_bone->data[mlx->ray.map_dochoi_y * 64
		+ (int)(mlx->ray.map_dochoi_x2)];
	else
		mlx->color = mlx->door.data[mlx->ray.map_dochoi_y * 64
		+ (int)(mlx->ray.map_dochoi_x2)];
	if (mlx->color != 0 && mlx->ray.idx >= 0
	&& mlx->ray.idx < mlx->win_h * mlx->win_w)
	{
		if (mlx->ray.sp_list->type != 3 || mlx->player.life == 0)
			set_dark(mlx, mlx->ray.sp_list->dist_sp);
		mlx->img.data[mlx->ray.idx] = mlx->color;
	}
}

void	show_sprite3(t_mlx *mlx)
{
	if (mlx->ray.ra < mlx->ray.min_rad_sp)
	{
		mlx->ray.cur = mlx->ray.ra + 2 * (M_PI);
		mlx->ray.min_max_cur_ra = ((mlx->ray.cur - mlx->ray.min_rad_sp) /
		(mlx->ray.max_rad_sp - mlx->ray.min_rad_sp)) * 64 - 0.000001;
	}
	while (++(mlx->ray.count_h) < (int)(mlx->ray.line_h_sp))
	{
		mlx->ray.map_dochoi_y = (int)((((float)(mlx->ray.count_h) +
		((mlx->ray.temp2 - mlx->ray.line_h_sp) / 2)) / mlx->ray.temp2) * 64);
		mlx->ray.count_w = mlx->ray.r;
		if (mlx->ray.map_dochoi_y < 0)
			mlx->ray.map_dochoi_y = 0;
		mlx->ray.idx = (mlx->ray.count_h + (int)(mlx->ray.line_o_sp))
		* (mlx->win_w) + mlx->ray.count_w;
		if (mlx->ray.map_dochoi_y >= 64)
			mlx->ray.map_dochoi_y = 63;
		if (mlx->ray.map_dochoi_y < 0)
			mlx->ray.map_dochoi_y = 0;
		mlx->ray.map_dochoi_x2 = lround(mlx->ray.min_max_cur_ra);
		show_sprite4(mlx);
	}
}

void	show_sprite2(t_mlx *mlx)
{
	if (mlx->ray.line_h_sp > mlx->win_h)
		mlx->ray.line_h_sp = mlx->win_h;
	mlx->ray.angle_user_to_sp = atan2(mlx->ray.dochoi_sp_y -
	mlx->player.y, mlx->ray.dochoi_sp_x - mlx->player.x);
	if (mlx->ray.angle_user_to_sp < 0)
		mlx->ray.angle_user_to_sp += 2 * M_PI;
	if (mlx->ray.angle_user_to_sp > 2 * M_PI)
		mlx->ray.angle_user_to_sp -= 2 * M_PI;
	mlx->ray.max_rad_sp = mlx->ray.angle_user_to_sp
	+ atan2(32.0, mlx->ray.dist2);
	mlx->ray.min_rad_sp = mlx->ray.angle_user_to_sp
	- atan2(32.0, mlx->ray.dist2);
	mlx->ray.cur = mlx->ray.ra;
	mlx->ray.min_max_cur_ra = ((mlx->ray.ra - mlx->ray.min_rad_sp) /
	(mlx->ray.max_rad_sp - mlx->ray.min_rad_sp)) * 64 - 0.000001;
	if (mlx->ray.ra > mlx->ray.max_rad_sp)
	{
		mlx->ray.cur = mlx->ray.ra - 2 * (M_PI);
		mlx->ray.min_max_cur_ra = ((mlx->ray.cur - mlx->ray.min_rad_sp) /
		(mlx->ray.max_rad_sp - mlx->ray.min_rad_sp)) * 64 - 0.000001;
	}
	show_sprite3(mlx);
}

void	set_sprite(t_mlx *mlx)
{
	if (mlx->ray.line_h_sp >= mlx->win_h)
	{
		mlx->ray.count_h -= (mlx->ray.line_h_sp - mlx->win_h);
		mlx->ray.line_h_sp = mlx->win_h - 1;
		if (mlx->ray.count_h < -1000)
			mlx->ray.count_h = -1000;
	}
}

void	show_sprite(t_mlx *mlx)
{
	ft_list_sort_sp(&(mlx->ray.sp_list));
	while (mlx->ray.sp_list)
	{
		mlx->ray.dochoi_sp_x = mlx->ray.sp_list->dochoi_sp_x;
		mlx->ray.dochoi_sp_y = mlx->ray.sp_list->dochoi_sp_y;
		mlx->ray.dist2 = dist(mlx->player.x, mlx->player.y,
		mlx->ray.dochoi_sp_x, mlx->ray.dochoi_sp_y);
		if (mlx->ray.dist2 <= mlx->ray.dist)
		{
			mlx->ray.line_h_sp = (64 * mlx->win_h) / mlx->ray.dist2;
			if (mlx->ray.line_o_sp < 0)
				mlx->ray.line_o_sp = 0;
			mlx->ray.temp2 = mlx->ray.line_h_sp;
			mlx->ray.count_h = -1;
			set_sprite(mlx);
			mlx->ray.line_o_sp = (mlx->win_h / 2) -
			mlx->ray.line_h_sp / 2 + mlx->player.jump_cnt;
			show_sprite2(mlx);
		}
		mlx->ray.sp_list = mlx->ray.sp_list->next;
	}
}
