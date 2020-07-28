/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 16:27:26 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 17:57:08 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
}

void	set_dark(t_mlx *mlx, float r_dist)
{
	float	dark_c;
	float	r;
	float	g;
	float	b;
	float	dist;

	dist = r_dist * 0.01;
	if (dist < 1)
		dist = 1.0;
	dark_c = 1 / (dist);
	r = (float)(mlx->color / 256 / 256) * dark_c;
	g = (float)((mlx->color / 256) % 256) * dark_c;
	b = (float)(mlx->color % 256) * dark_c;
	mlx->color = (int)(r) * (256 * 256) + (int)(g) * 256 + (int)b;
	if (mlx->player.life == 0)
		mlx->color = (int)(255 - r) * (256 * 256) + (int)(255 - g)
		* 256 + (int)(255 - b);
}

void	show_hud(t_mlx *mlx)
{
	int	i;
	int	j;
	int half_h;
	int	half_w;

	i = 0;
	half_h = mlx->win_h / 2 + (mlx->win_h % 2);
	half_w = mlx->win_w / 2 + (mlx->win_w % 2);
	while (i < 24)
	{
		j = 0;
		while (j < 24)
		{
			if (mlx->hud.data[i * 24 + j] != 0)
				mlx->img.data[(i + half_h)
				* (mlx->win_w) + j + half_w] = mlx->hud.data[i * 24 + j];
			j++;
		}
		i++;
	}
}
