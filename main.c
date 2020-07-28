/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:05:07 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:33:01 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

int		ft_close(void *param)
{
	(void)param;
	exit(0);
}

void	ani_parse(t_mlx *mlx)
{
	mlx->ani[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"./textures/fire1.xpm",
	&(mlx->ani[0].height), &(mlx->ani[0].width));
	if (!(mlx->ani[0].img_ptr))
		display_error("ani's Path not found.");
	mlx->ani[0].data = (int*)mlx_get_data_addr(mlx->ani[0].img_ptr,
	&mlx->ani[0].bpp, &mlx->ani[0].size_l, &mlx->ani[0].endian);
	mlx->ani[1].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"./textures/fire2.xpm",
	&(mlx->ani[1].height), &(mlx->ani[1].width));
	if (!(mlx->ani[1].img_ptr))
		display_error("ani's Path not found.");
	mlx->ani[1].data = (int*)mlx_get_data_addr(mlx->ani[1].img_ptr,
	&mlx->ani[1].bpp, &mlx->ani[1].size_l, &mlx->ani[1].endian);
	mlx->ani[2].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"./textures/fire3.xpm",
	&(mlx->ani[2].height), &(mlx->ani[2].width));
	if (!(mlx->ani[2].img_ptr))
		display_error("ani's Path not found.");
	mlx->ani[2].data = (int*)mlx_get_data_addr(mlx->ani[2].img_ptr,
	&mlx->ani[2].bpp, &mlx->ani[2].size_l, &mlx->ani[2].endian);
}

void	hud_parse(t_mlx *mlx)
{
	mlx->hud.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"./textures/hud.xpm", &(mlx->hud.height), &(mlx->hud.width));
	if (!(mlx->hud.img_ptr))
		display_error("hud's Path not found.");
	mlx->hud.data = (int*)mlx_get_data_addr(mlx->hud.img_ptr,
	&mlx->hud.bpp, &mlx->hud.size_l, &mlx->hud.endian);
	mlx->door.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
	"./textures/pillar.xpm", &(mlx->door.height), &(mlx->door.width));
	if (!(mlx->door.img_ptr))
		display_error("door's Path not found.");
	mlx->door.data = (int*)mlx_get_data_addr(mlx->door.img_ptr,
	&mlx->door.bpp, &mlx->door.size_l, &mlx->door.endian);
}

int		main(int argc, char *argv[])
{
	t_mlx	mlx;

	map_init(&mlx);
	if (argc != 2)
	{
		if (argc == 3 && !ft_strncmp("--save", argv[2], 7))
			mlx.save_flag = 1;
		else
			display_error("invalid arg");
	}
	mlx.mlx_ptr = mlx_init();
	map_parse(&mlx, argv[1]);
	player_set(&mlx);
	mlx.win = mlx_new_window(mlx.mlx_ptr, mlx.win_w, mlx.win_h, "dochoi_cub3D");
	map_check(&mlx);
	ani_parse(&mlx);
	hud_parse(&mlx);
	mlx_hook(mlx.win, KEY_PRESS_EVENT, 0, key_press_event_func, &mlx);
	mlx_hook(mlx.win, KEY_RELEASE_EVENT, 0, key_release_event_func, &mlx);
	mlx_hook(mlx.win, MOUSE_X_EVENT, 0, ft_close, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, dochoi_show, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
