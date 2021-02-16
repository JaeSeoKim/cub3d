/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 23:46:07 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 17:09:22 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	parsing_sprite(t_cub3d *g, t_list **lst, t_list **curr)
{
	int			i;
	t_sprite	*tmp;

	*lst = 0;
	i = -1;
	while (++i < g->map.w * g->map.h)
	{
		if (g->map.data[i / g->map.w][i % g->map.w] == '2')
		{
			if (!(tmp = malloc(sizeof(t_sprite))))
				exit_cub3d_msg(g, "malloc failed");
			tmp->pos = new_vec(i % g->map.w + 0.5, i / g->map.w + 0.5);
			tmp->tex = &g->tex[S];
			if (!*lst)
				(!(*lst = ft_lstnew(tmp)) ?
					exit_cub3d_msg(g, "malloc failed") : 0);
			else if (!(*curr = ft_lstnew(tmp)))
				exit_cub3d_msg(g, "malloc failed");
			else
				ft_lstadd_back(lst, *curr);
		}
	}
}

void	init_sprite(t_cub3d *g)
{
	int			i;
	t_list		*lst;
	t_list		*curr;

	parsing_sprite(g, &lst, &curr);
	g->num_sp = ft_lstsize(lst);
	if (!(g->sp = malloc(sizeof(t_sprite) * g->num_sp)) ||
		!(g->sp_order = malloc(sizeof(int) * g->num_sp)) ||
		!(g->sp_dist = malloc(sizeof(float) * g->num_sp)))
		exit_cub3d_msg(g, "malloc failed");
	curr = lst;
	i = -1;
	while (++i < g->num_sp)
	{
		g->sp[i] = *(t_sprite *)curr->content;
		curr = curr->next;
	}
	ft_lstclear(&lst, free);
}
