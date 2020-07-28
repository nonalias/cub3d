/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:17:19 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:32:51 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

int		what_flag_s(char **strs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read S_flag"));
	mlx->sp.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, strs[1],
	&(mlx->sp.height), &(mlx->sp.width));
	if (!(mlx->sp.img_ptr))
		return (display_error("S's Path not found."));
	mlx->sp.data = (int*)mlx_get_data_addr(mlx->sp.img_ptr,
	&mlx->sp.bpp, &mlx->sp.size_l, &mlx->sp.endian);
	mlx->flag_check[5] = 1;
	return (0);
}

int		what_flag_f(char **strs, t_mlx *mlx)
{
	int		i;
	char	**rgbs;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read F_flag"));
	if (!(rgbs = ft_split(strs[1], ',')))
		return (display_error("F's RGB values not found."));
	while (rgbs[i])
		i++;
	if (i != 3)
		return (display_error("Unalbe F's RGB values"));
	mlx->f_color = 65536 * ft_atoi(rgbs[0]) + (256 * ft_atoi(rgbs[1]))
	+ ft_atoi(rgbs[2]);
	mlx->flag_check[6] = 1;
	split_free(rgbs);
	return (0);
}

int		what_flag_c(char **strs, t_mlx *mlx)
{
	int		i;
	char	**rgbs;

	i = 0;
	while (strs[i])
		i++;
	if (i != 2)
		return (display_error("Unable to read F_flag"));
	if (!(rgbs = ft_split(strs[1], ',')))
		return (display_error("C's RGB values not found."));
	while (rgbs[i])
		i++;
	if (i != 3)
		return (display_error("Unalbe C's RGB values"));
	mlx->c_color = 65536 * ft_atoi(rgbs[0]) + (256 * ft_atoi(rgbs[1]))
	+ ft_atoi(rgbs[2]);
	mlx->flag_check[7] = 1;
	split_free(rgbs);
	return (0);
}

void	split_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
