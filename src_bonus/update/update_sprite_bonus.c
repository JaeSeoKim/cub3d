/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:54:49 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 01:51:25 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	compare(t_list *a, t_list *b)
{
	t_sprite	*sp_a;
	t_sprite	*sp_b;

	sp_a = (t_sprite *)a->content;
	sp_b = (t_sprite *)b->content;
	if (sp_a->dist < sp_b->dist)
		return (1);
	return (0);
}

static void	update_sprite_dist(t_cub3d *g)
{
	t_list		*curr;
	t_sprite	*sp;

	curr = g->sp;
	while (curr)
	{
		sp = ((t_sprite *)curr->content);
		sp->dist = \
			(g->pos.x - sp->pos.x) * (g->pos.x - sp->pos.x)
			+ (g->pos.y - sp->pos.y) * (g->pos.y - sp->pos.y);
		curr = curr->next;
	}
}

void		update_sprite(t_cub3d *g)
{
	float		inv_det;
	t_vec		pos;
	t_list		*curr;
	t_sprite	*sp;

	update_sprite_dist(g);
	(g->sp ? ft_lstsort(&g->sp, compare) : 0);
	curr = g->sp;
	while (curr)
	{
		sp = curr->content;
		pos.x = sp->pos.x - g->pos.x;
		pos.y = sp->pos.y - g->pos.y;
		inv_det = 1.0 / (g->plane.x * g->dir.y - g->dir.x * g->plane.y);
		sp->trans.x = inv_det * (g->dir.y * pos.x - g->dir.x * pos.y);
		sp->trans.y = inv_det * (-g->plane.y * pos.x + g->plane.x * pos.y);
		curr = curr->next;
	}
}
