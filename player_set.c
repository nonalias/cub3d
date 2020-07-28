/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:24:32 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 14:05:09 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

void	player_set(t_mlx *mlx)
{
	if (mlx->dir == 'N')
		mlx->player.angle = M_PI * 1.5;
	else if (mlx->dir == 'S')
		mlx->player.angle = M_PI / 2;
	else if (mlx->dir == 'W')
		mlx->player.angle = M_PI;
	else if (mlx->dir == 'E')
		mlx->player.angle = 0;
	mlx->player.dx = cos(mlx->player.angle) * 5;
	mlx->player.dy = sin(mlx->player.angle) * 5;
	mlx->player.jump_cnt = 0;
	mlx->player.down_cnt = 0;
	mlx->player.life = 100;
	mlx->max_dof = mlx->map_h;
	if (mlx->map_w > mlx->map_h)
		mlx->max_dof = mlx->map_w;
	mlx->cnt = 0;
	mlx->ray.die = 0;
}
