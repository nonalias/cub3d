/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 20:52:07 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:32:54 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

static void	h_check4(t_mlx *mlx)
{
	mlx->ray.rx += mlx->ray.xo;
	mlx->ray.ry += mlx->ray.yo;
	mlx->ray.dof += 1;
}

static void	h_check3(t_mlx *mlx)
{
	if (mlx->ray.mx >= 0 && mlx->ray.my >= 0 &&
		mlx->ray.mx < (mlx->map_w) && mlx->ray.my < (mlx->map_h) &&
		mlx->map[mlx->ray.my][mlx->ray.mx] == 1)
	{
		mlx->ray.hx = mlx->ray.rx;
		mlx->ray.hy = mlx->ray.ry;
		mlx->ray.dist_h = dist(mlx->player.x,
		mlx->player.y, mlx->ray.hx, mlx->ray.hy);
		mlx->ray.dof = mlx->max_dof;
		if (mlx->player.y > mlx->ray.ry)
		{
			mlx->ray.map_dochoi_x = mlx->ray.rx - (float)(mlx->ray.mx << 6);
			mlx->ray.h_so_flag = 1;
		}
		else
			mlx->ray.map_dochoi_x =
			64 - (mlx->ray.rx - (float)(mlx->ray.mx << 6));
		if (mlx->ray.map_dochoi_x < 0)
			mlx->ray.map_dochoi_x = 0;
	}
	else
		h_check4(mlx);
}

static void	h_check2(t_mlx *mlx)
{
	while (mlx->ray.dof < mlx->max_dof)
	{
		mlx->ray.mx = (int)(mlx->ray.rx) >> 6;
		mlx->ray.my = (int)(mlx->ray.ry) >> 6;
		mlx->ray.mp = mlx->ray.my * mlx->map_w + mlx->ray.mx;
		if (mlx->ray.my >= 0 && mlx->ray.mx >= 0 &&
		mlx->ray.mx < (mlx->map_w) &&
		mlx->ray.my < (mlx->map_h) && mlx->map[mlx->ray.my][mlx->ray.mx] >= 2)
		{
			mlx->ray.sp_type = mlx->map[mlx->ray.my][mlx->ray.mx];
			mlx->ray.dochoi_sp_x = ((float)(mlx->ray.mx) + 0.5) * 64;
			mlx->ray.dochoi_sp_y = ((float)(mlx->ray.my) + 0.5) * 64;
			mlx->ray.dist_sp_h = dist(mlx->player.x, mlx->player.y,
			mlx->ray.rx, mlx->ray.ry);
			ft_lstadd_back_sp(&(mlx->ray.sp_list),
			ft_lstnew_sp(mlx, 0, mlx->ray.mx, mlx->ray.my));
		}
		h_check3(mlx);
	}
}

void		h_init(t_mlx *mlx)
{
	mlx->ray.h_so_flag = 0;
	mlx->ray.dof = 0;
	mlx->ray.dist_h = 1000000;
	mlx->ray.hx = mlx->player.x;
	mlx->ray.hy = mlx->player.y;
	mlx->ray.atan_ra = -1 / tan(mlx->ray.ra);
	mlx->ray.dist_sp = 0;
}

void		h_check(t_mlx *mlx)
{
	h_init(mlx);
	if (mlx->ray.ra > M_PI)
	{
		mlx->ray.ry = (((int)(mlx->player.y) >> 6) << 6) - 0.0001;
		mlx->ray.rx = (mlx->player.y - mlx->ray.ry) * mlx->ray.atan_ra
		+ mlx->player.x;
		mlx->ray.yo = -64;
		mlx->ray.xo = -mlx->ray.yo * mlx->ray.atan_ra;
	}
	else if (mlx->ray.ra < M_PI)
	{
		mlx->ray.ry = (((int)(mlx->player.y) >> 6) << 6) + 64;
		mlx->ray.rx = (mlx->player.y - mlx->ray.ry) * mlx->ray.atan_ra
		+ mlx->player.x;
		mlx->ray.yo = 64;
		mlx->ray.xo = -mlx->ray.yo * mlx->ray.atan_ra;
	}
	if (mlx->ray.ra == 0 || mlx->ray.ra == M_PI)
	{
		mlx->ray.rx = mlx->player.x;
		mlx->ray.ry = mlx->player.y;
		mlx->ray.dof = mlx->max_dof;
	}
	h_check2(mlx);
}
