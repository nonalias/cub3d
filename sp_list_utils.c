/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 20:13:21 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:33:33 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

void		ft_lstadd_back_sp(t_sp_list **lst, t_sp_list *new)
{
	t_sp_list	*ptr;

	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void		ft_lstclear_sp(t_sp_list **lst)
{
	t_sp_list	*ptr;

	if (lst == 0 || *lst == 0)
		return ;
	while ((*lst))
	{
		ptr = (*lst);
		(*lst) = (*lst)->next;
		free(ptr);
	}
}

t_sp_list	*ft_lstnew_sp(t_mlx *mlx, int is_v, int mx, int my)
{
	t_sp_list	*lst;

	if (!(lst = (t_sp_list*)malloc(sizeof(t_sp_list))))
		return (0);
	lst->dochoi_sp_x = mlx->ray.dochoi_sp_x;
	lst->dochoi_sp_y = mlx->ray.dochoi_sp_y;
	if (is_v == 1)
		lst->dist_sp = mlx->ray.dist_sp_v;
	else
		lst->dist_sp = mlx->ray.dist_sp_h;
	lst->mx = mx;
	lst->my = my;
	lst->type = mlx->ray.sp_type;
	lst->next = 0;
	return (lst);
}
