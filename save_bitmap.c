/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:43:32 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:33:17 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

static int	extract_color(t_mlx *mlx, int x, int y)
{
	int	rgb;
	int	color;

	color = mlx->img.data[x + (mlx->win_h - 1 - y) *\
												mlx->win_w];
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int	fill_bmp_color(int fd, t_mlx *mlx, int pad)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				color;

	ft_memset(zero, 0, 3);
	y = 0;
	while (y < mlx->win_h)
	{
		x = 0;
		while (x < mlx->win_w)
		{
			color = extract_color(mlx, x, y);
			if (write(fd, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(fd, &zero, pad) < 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static void	int_to_char(unsigned char *num, int value)
{
	num[0] = (unsigned char)(value);
	num[1] = (unsigned char)(value >> 8);
	num[2] = (unsigned char)(value >> 16);
	num[3] = (unsigned char)(value >> 24);
}

static int	write_bmp_header(int fd, int file_size, t_mlx *mlx)
{
	unsigned char bmp_file_header[14];
	unsigned char bmp_info_header[40];

	ft_memset(bmp_file_header, 0, 14);
	bmp_file_header[0] = (unsigned char)('B');
	bmp_file_header[1] = (unsigned char)('M');
	int_to_char(bmp_file_header + 2, file_size);
	bmp_file_header[10] = (unsigned char)(54);
	if (write(fd, bmp_file_header, 14) < 0)
		return (0);
	ft_memset(bmp_info_header, 0, 40);
	bmp_info_header[0] = (unsigned char)(40);
	int_to_char(bmp_info_header + 4, mlx->win_w);
	int_to_char(bmp_info_header + 8, mlx->win_h);
	bmp_info_header[12] = (unsigned char)(1);
	bmp_info_header[14] = (unsigned char)(24);
	if (write(fd, bmp_info_header, 40) < 0)
		return (0);
	return (1);
}

int			save_bmp(t_mlx *mlx)
{
	int fd;
	int file_size;
	int pad;

	fd = 0;
	pad = (4 - (mlx->win_w * 3) % 4) % 4;
	if ((fd = open("savefile.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644)) < 0)
		return (0);
	file_size = 54 + ((mlx->win_w + pad) * mlx->win_h);
	if (!write_bmp_header(fd, file_size, mlx))
		return (0);
	if (!fill_bmp_color(fd, mlx, pad))
		return (0);
	close(fd);
	exit(0);
	return (1);
}
