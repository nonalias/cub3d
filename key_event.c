/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 19:09:53 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 13:45:29 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

int			key_press_event_func(int keycode, t_mlx *mlx)
{
	if (keycode >= 300)
		return (-1);
	mlx->key_check[keycode] = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int			key_release_event_func(int keycode, t_mlx *mlx)
{
	if (keycode >= 300)
		return (-1);
	mlx->key_check[keycode] = 0;
	return (0);
}

static void	key_loop3(t_mlx *mlx)
{
	if (mlx->key_check[KEY_LEFT])
	{
		mlx->player.angle -= 0.1;
		mlx->player.angle < 0 ? mlx->player.angle += 2 * M_PI : 0;
		mlx->player.dx = cos(mlx->player.angle) * 5;
		mlx->player.dy = sin(mlx->player.angle) * 5;
	}
	else if (mlx->key_check[KEY_RIGHT])
	{
		mlx->player.angle += 0.1;
		mlx->player.angle > 2 * M_PI ? mlx->player.angle -= 2 * M_PI : 0;
		mlx->player.dx = cos(mlx->player.angle) * 5;
		mlx->player.dy = sin(mlx->player.angle) * 5;
	}
	if (mlx->key_check[KEY_JUMP])
	{
		if (!(mlx->player.jump_cnt) && !(mlx->player.down_cnt))
		{
			mlx->player.down_cnt = 1;
		}
	}
}

static void	key_loop2(t_mlx *mlx)
{
	if (mlx->key_check[KEY_W])
	{
		mlx->player.y += mlx->player.dy;
		mlx->player.x += mlx->player.dx;
	}
	else if (mlx->key_check[KEY_S])
	{
		mlx->player.y -= mlx->player.dy;
		mlx->player.x -= mlx->player.dx;
	}
	key_loop3(mlx);
}

void		key_loop(t_mlx *mlx)
{
	mlx->ray.prey = mlx->player.y;
	mlx->ray.prex = mlx->player.x;
	if (mlx->key_check[KEY_A])
	{
		mlx->player.y -= mlx->player.dx;
		mlx->player.x += mlx->player.dy;
	}
	else if (mlx->key_check[KEY_D])
	{
		mlx->player.y += mlx->player.dx;
		mlx->player.x -= mlx->player.dy;
	}
	key_loop2(mlx);
	if (mlx->map[(int)(mlx->player.y / 64)][(int)(mlx->player.x / 64)] >= 1)
	{
		if (mlx->map[(int)(mlx->player.y / 64)][(int)(mlx->player.x / 64)] == 3)
			if (mlx->player.life > 0)
				mlx->player.life -= 1;
		if (mlx->map[(int)(mlx->player.y / 64)][(int)(mlx->player.x / 64)] == 4)
			if (mlx->player.life < 5)
				return ;
		mlx->player.y = mlx->ray.prey;
		mlx->player.x = mlx->ray.prex;
	}
}
