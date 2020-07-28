/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_check2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:28:33 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:33:38 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

static void	v_check4(t_mlx *mlx)
{
	mlx->ray.rx += mlx->ray.xo;
	mlx->ray.ry += mlx->ray.yo;
	mlx->ray.dof += 1;
}

void		v_check3(t_mlx *mlx)
{
	if (mlx->ray.mx >= 0 && mlx->ray.my >= 0 &&
		mlx->ray.mx < (mlx->map_w) &&
		mlx->ray.my < (mlx->map_h) && mlx->map[mlx->ray.my][mlx->ray.mx] == 1)
	{
		mlx->ray.vx = mlx->ray.rx;
		mlx->ray.vy = mlx->ray.ry;
		mlx->ray.dist_v = dist(mlx->player.x,
		mlx->player.y, mlx->ray.vx, mlx->ray.vy);
		mlx->ray.dof = mlx->max_dof;
		if (mlx->player.x < mlx->ray.rx)
		{
			mlx->ray.map_dochoi_x2 = mlx->ray.ry - (float)(mlx->ray.my << 6);
			mlx->ray.v_ea_flag = 1;
		}
		else
			mlx->ray.map_dochoi_x2 =
			64 - (mlx->ray.ry - (float)(mlx->ray.my << 6));
		if (mlx->ray.map_dochoi_x2 < 0)
			mlx->ray.map_dochoi_x2 = 0;
	}
	else
		v_check4(mlx);
}
