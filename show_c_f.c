/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_c_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:21:24 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:33:24 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

static void	show_c_f2(t_mlx *mlx, int i, int j, int half)
{
	while (i < half + mlx->player.jump_cnt)
	{
		j = 0;
		while (j < mlx->win_w)
		{
			mlx->img.data[i * (mlx->win_w) + j] = mlx->c_color;
			j++;
		}
		i++;
	}
}

void		show_c_f(t_mlx *mlx)
{
	int	i;
	int	j;
	int half;

	i = 0;
	half = mlx->win_h / 2 + (mlx->win_h % 2);
	while (i < half)
	{
		j = 0;
		while (j < mlx->win_w)
		{
			mlx->img.data[i * (mlx->win_w) + j] = mlx->c_color;
			mlx->img.data[(i + half) * (mlx->win_w) + j] = mlx->f_color;
			j++;
		}
		i++;
	}
	show_c_f2(mlx, i, j, half);
}
