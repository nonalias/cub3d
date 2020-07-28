/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:10:37 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 13:52:01 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

void	show_life(t_mlx *mlx)
{
	int	i;
	int	j;
	int half_h;
	int	half_w;

	i = 0;
	half_h = mlx->win_h / 2 + (mlx->win_h % 2) + mlx->win_h / 4;
	half_w = mlx->win_w / 2 + (mlx->win_w % 2) - mlx->win_w / 4;
	if (i < 0)
		return ;
	while (i < mlx->player.life * 3)
	{
		j = half_h;
		while (j < half_h + 20)
		{
			mlx->img.data[j * (mlx->win_w) + half_w + i] = 0xff0000;
			j++;
		}
		i++;
	}
}
