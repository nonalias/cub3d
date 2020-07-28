/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 20:52:07 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 13:54:04 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

t_sp_list	*ft_lstiter_check(t_sp_list *lst, t_mlx *mlx)
{
	if (lst == 0)
		return (0);
	while (lst)
	{
		if (lst->my == mlx->ray.my && lst->mx == mlx->ray.mx)
			return (lst);
		lst = lst->next;
	}
	return (0);
}

static void	v_check2_2(t_mlx *mlx)
{
	t_sp_list	*temp;

	mlx->ray.dist_sp_v = dist(mlx->player.x, mlx->player.y,
	mlx->ray.rx, mlx->ray.ry);
	mlx->ray.dochoi_sp_x = ((float)(mlx->ray.mx) + 0.5) * 64;
	mlx->ray.dochoi_sp_y = ((float)(mlx->ray.my) + 0.5) * 64;
	mlx->ray.sp_type = mlx->map[mlx->ray.my][mlx->ray.mx];
	if (!(temp = ft_lstiter_check(mlx->ray.sp_list, mlx)))
	{
		ft_lstadd_back_sp(&(mlx->ray.sp_list),
		ft_lstnew_sp(mlx, 1, mlx->ray.mx, mlx->ray.my));
	}
	else if (temp->dist_sp >= mlx->ray.dist_sp_v)
		temp->dist_sp = mlx->ray.dist_sp_v;
}

static void	v_check2(t_mlx *mlx)
{
	while (mlx->ray.dof < mlx->max_dof)
	{
		mlx->ray.mx = (int)(mlx->ray.rx) >> 6;
		mlx->ray.my = (int)(mlx->ray.ry) >> 6;
		mlx->ray.mp = mlx->ray.my * mlx->map_w + mlx->ray.mx;
		if (mlx->ray.my >= 0 && mlx->ray.mx >= 0 && mlx->ray.mx < (mlx->map_w)
		&& mlx->ray.my < (mlx->map_h) &&
		mlx->map[mlx->ray.my][mlx->ray.mx] >= 2)
			v_check2_2(mlx);
		v_check3(mlx);
	}
}

void		v_init(t_mlx *mlx)
{
	mlx->ray.v_ea_flag = 0;
	mlx->ray.dof = 0;
	mlx->ray.dist_v = 1000000;
	mlx->ray.vx = mlx->player.x;
	mlx->ray.vy = mlx->player.y;
	mlx->ray.n_tan = -tan(mlx->ray.ra);
}

void		v_check(t_mlx *mlx)
{
	v_init(mlx);
	if (mlx->ray.ra > M_PI / 2 && mlx->ray.ra < 3 * M_PI / 2)
	{
		mlx->ray.rx = (((int)(mlx->player.x) >> 6) << 6) - 0.0001;
		mlx->ray.ry = (mlx->player.x - mlx->ray.rx) * mlx->ray.n_tan
		+ mlx->player.y;
		mlx->ray.xo = -64;
		mlx->ray.yo = -mlx->ray.xo * mlx->ray.n_tan;
	}
	else if (mlx->ray.ra < M_PI / 2 || mlx->ray.ra > 3 * M_PI / 2)
	{
		mlx->ray.rx = (((int)(mlx->player.x) >> 6) << 6) + 64;
		mlx->ray.ry = (mlx->player.x - mlx->ray.rx) * mlx->ray.n_tan
		+ mlx->player.y;
		mlx->ray.xo = 64;
		mlx->ray.yo = -mlx->ray.xo * mlx->ray.n_tan;
	}
	if (mlx->ray.ra == 0 || mlx->ray.ra == M_PI)
	{
		mlx->ray.rx = mlx->player.x;
		mlx->ray.ry = mlx->player.y;
		mlx->ray.dof = mlx->max_dof;
	}
	v_check2(mlx);
}
