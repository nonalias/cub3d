/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dochoi_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 19:39:46 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 14:06:41 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

void	r_init(t_mlx *mlx)
{
	mlx->ray.sp_flag = 0;
	mlx->ray.dist_sp = 0;
	mlx->ray.dist_sp_h = 1000000;
	mlx->ray.dist_sp_v = 1000000;
	mlx->ray.v_close_flag = 0;
	mlx->ray.dist2 = 0;
	ft_lstclear_sp(&(mlx->ray.sp_list));
}

void	set_ani(t_mlx *mlx)
{
	mlx->cnt--;
	if (mlx->cnt < 0)
		mlx->cnt = 8;
	mlx->ani_bone = &(mlx->ani[mlx->cnt / 3]);
}

void	r_shoot(t_mlx *mlx)
{
	set_ani(mlx);
	if (mlx->player.down_cnt == 1)
		mlx->player.jump_cnt += 5;
	else if (mlx->player.down_cnt == 2 && mlx->player.jump_cnt > 0)
	{
		mlx->player.jump_cnt -= 5;
		if (mlx->player.jump_cnt == 0)
			mlx->player.down_cnt = 0;
	}
	if (mlx->player.down_cnt == 1 && mlx->player.jump_cnt == 100)
		mlx->player.down_cnt = 2;
	while (++(mlx->ray.r) < mlx->win_w)
	{
		r_init(mlx);
		h_check(mlx);
		v_check(mlx);
		show_wall(mlx);
		show_sprite(mlx);
	}
	show_hud(mlx);
	show_life(mlx);
	if (mlx->save_flag)
		save_bmp(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
}

int		dochoi_show(t_mlx *mlx)
{
	key_loop(mlx);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_w, mlx->win_h);
	mlx->img.data = (int*)mlx_get_data_addr(mlx->img.img_ptr,
	&(mlx->img.bpp), &(mlx->img.size_l), &(mlx->img.endian));
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx->ray.ra = mlx->player.angle - (DR * 30);
	if (mlx->ray.ra < 0)
		mlx->ray.ra += 2 * M_PI;
	else if (mlx->ray.ra > 2 * M_PI)
		mlx->ray.ra -= 2 * M_PI;
	mlx->ray.dr_dochoi = (DR / (mlx->win_w / 60));
	mlx->ray.r = -1;
	if (mlx->player.life == 0 && !mlx->ray.die)
	{
		mlx->ray.die = 1;
		mlx->f_color = (~mlx->f_color) & 131071;
		mlx->c_color = (~mlx->c_color) & 131071;
	}
	show_c_f(mlx);
	r_shoot(mlx);
	return (0);
}
