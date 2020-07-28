/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:07:01 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:32:48 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

int	what_flag_r(char **strs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 3)
		return (display_error("Unable to read R_flag"));
	mlx->win_w = ft_atoi(strs[1]);
	mlx->win_h = ft_atoi(strs[2]);
	if (mlx->win_w > MAX_WIN_WIDTH)
		mlx->win_w = MAX_WIN_WIDTH;
	if (mlx->win_w < MIN_WIN_WIDTH)
		mlx->win_w = MIN_WIN_WIDTH;
	if (mlx->win_h > MAX_WIN_HEIGHT)
		mlx->win_h = MAX_WIN_HEIGHT;
	if (mlx->win_h < MIN_WIN_HEIGHT)
		mlx->win_h = MAX_WIN_HEIGHT;
	mlx->flag_check[0] = 1;
	return (0);
}

int	what_flag_no(char **strs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read NO_flag"));
	mlx->no_wall.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, strs[1],
	&(mlx->no_wall.height), &(mlx->no_wall.width));
	if (!(mlx->no_wall.img_ptr))
		return (display_error("NO's Path not found."));
	mlx->no_wall.data = (int*)mlx_get_data_addr(mlx->no_wall.img_ptr,
	&mlx->no_wall.bpp, &mlx->no_wall.size_l, &mlx->no_wall.endian);
	mlx->flag_check[1] = 1;
	return (0);
}

int	what_flag_so(char **strs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read SO_flag"));
	mlx->so_wall.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, strs[1],
	&(mlx->so_wall.height), &(mlx->so_wall.width));
	if (!(mlx->so_wall.img_ptr))
		return (display_error("SO's Path not found."));
	mlx->so_wall.data = (int*)mlx_get_data_addr(mlx->so_wall.img_ptr,
	&mlx->so_wall.bpp, &mlx->so_wall.size_l, &mlx->so_wall.endian);
	mlx->flag_check[2] = 1;
	return (0);
}

int	what_flag_we(char **strs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read WE_flag"));
	mlx->we_wall.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, strs[1],
	&(mlx->we_wall.height), &(mlx->we_wall.width));
	if (!(mlx->we_wall.img_ptr))
		return (display_error("WE's Path not found."));
	mlx->we_wall.data = (int*)mlx_get_data_addr(mlx->we_wall.img_ptr,
	&mlx->we_wall.bpp, &mlx->we_wall.size_l, &mlx->we_wall.endian);
	mlx->flag_check[3] = 1;
	return (0);
}

int	what_flag_ea(char **strs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read EA_flag"));
	mlx->ea_wall.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, strs[1],
	&(mlx->ea_wall.height), &(mlx->ea_wall.width));
	if (!(mlx->ea_wall.img_ptr))
		return (display_error("EA's Path not found."));
	mlx->ea_wall.data = (int*)mlx_get_data_addr(mlx->ea_wall.img_ptr,
	&mlx->ea_wall.bpp, &mlx->ea_wall.size_l, &mlx->ea_wall.endian);
	mlx->flag_check[4] = 1;
	return (0);
}
