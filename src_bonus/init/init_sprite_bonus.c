/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 23:46:07 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/25 00:54:50 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*check_tex(t_cub3d *g, t_sprite *sp, char c)
{
	if (c == 'Y')
	{
		sp->tex = &g->tex[S_Y];
		sp->base = S_Y;
	}
	else if (c == 'R')
	{
		sp->tex = &g->tex[S_R];
		sp->base = S_R;
	}
	else if (c == 'G')
	{
		sp->tex = &g->tex[S_G];
		sp->base = S_G;
	}
	else if (c == 'B')
	{
		sp->tex = &g->tex[S_B];
		sp->base = S_B;
	}
	return (0);
}

void			parsing_sprite(t_cub3d *g, t_list **lst, t_list **curr)
{
	int			i;
	t_sprite	*tmp;

	*lst = 0;
	i = -1;
	while (++i < g->map.w * g->map.h)
	{
		if (ft_strchr("YRGB", g->map.data[i / g->map.w][i % g->map.w]))
		{
			if (!(tmp = malloc(sizeof(t_sprite))))
				exit_cub3d_msg(g, "malloc failed");
			tmp->pos = new_vec(i % g->map.w + 0.5, i / g->map.w + 0.5);
			check_tex(g, tmp, g->map.data[i / g->map.w][i % g->map.w]);
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

void			init_sprite(t_cub3d *g)
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
