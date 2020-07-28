/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 20:40:22 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/20 16:32:59 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dochoi_cub3d.h"

unsigned int	ft_list_size(t_sp_list *begin_list)
{
	t_sp_list			*ptr;
	unsigned int		i;

	if (begin_list == 0)
		return (0);
	i = 1;
	ptr = begin_list;
	while (ptr->next != 0)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

t_sp_list		*ft_list_at(t_sp_list *begin_list, unsigned int nbr)
{
	unsigned int		i;
	t_sp_list			*ptr;

	ptr = begin_list;
	i = 0;
	while (i != nbr)
	{
		ptr = ptr->next;
		if (ptr == 0)
			return (0);
		i++;
	}
	return (ptr);
}

void			smaller(t_sp_list **pre_ptr,
		t_sp_list **begin_list, t_sp_list **ptr, t_sp_list **ptr2)
{
	if (*pre_ptr)
		(*pre_ptr)->next = *ptr2;
	else
		begin_list[0] = *ptr2;
	*pre_ptr = *ptr;
	(*ptr)->next = (*ptr2)->next;
	(*ptr2)->next = (*pre_ptr);
}

static int		cmp(float a, float b)
{
	return (a < b);
}

void			ft_list_sort_sp(t_sp_list **begin_list)
{
	unsigned int			i;
	unsigned int			j;
	t_sp_list				*ptr2;
	t_sp_list				*ptr;
	t_sp_list				*pre_ptr;

	if (begin_list == 0 || *begin_list == 0)
		return ;
	i = ft_list_size(begin_list[0]) - 1;
	pre_ptr = 0;
	while (i > 0)
	{
		j = -1;
		while (++j < i)
		{
			pre_ptr = 0;
			if (j > 0)
				pre_ptr = ft_list_at(*begin_list, j - 1);
			ptr = ft_list_at(begin_list[0], j);
			ptr2 = ft_list_at(begin_list[0], j + 1);
			if (cmp(ptr->dist_sp, ptr2->dist_sp) > 0)
				smaller(&pre_ptr, begin_list, &ptr, &ptr2);
		}
		i--;
	}
}
