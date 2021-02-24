/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:54:49 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/25 01:03:22 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	sort_sprite(t_cub3d *g)
{
	int			tmp_o;
	float		tmp_d;
	float		max;
	t_ivec		iv;

	iv.x = -1;
	while (++iv.x < g->num_sp - 1)
	{
		max = g->sp_dist[iv.x];
		iv.y = iv.x;
		while (++iv.y < g->num_sp)
		{
			if (max < g->sp_dist[iv.y] && (max = g->sp_dist[iv.y]))
			{
				tmp_o = g->sp_order[iv.x];
				g->sp_order[iv.x] = g->sp_order[iv.y];
				g->sp_order[iv.y] = tmp_o;
				tmp_d = g->sp_dist[iv.x];
				g->sp_dist[iv.x] = g->sp_dist[iv.y];
				g->sp_dist[iv.y] = tmp_d;
			}
		}
	}
}

void		update_sprite(t_cub3d *g)
{
	int			i;
	float		inv_det;
	t_vec		pos;
	t_sprite	*sp;

	i = -1;
	while (++i < g->num_sp)
	{
		g->sp_order[i] = i;
		g->sp_dist[i] = \
			(g->pos.x - g->sp[i].pos.x) * (g->pos.x - g->sp[i].pos.x)
			+ (g->pos.y - g->sp[i].pos.y) * (g->pos.y - g->sp[i].pos.y);
	}
	((i = -1) == -1 ? sort_sprite(g) : 0);
	while (++i < g->num_sp)
	{
		sp = &g->sp[g->sp_order[i]];
		sp->tex = &g->tex[sp->base + ((int)g->count % 2 == 0 ? 1 : 0)];
		pos.x = sp->pos.x - g->pos.x;
		pos.y = sp->pos.y - g->pos.y;
		inv_det = 1.0 / (g->plane.x * g->dir.y - g->dir.x * g->plane.y);
		sp->trans.x = inv_det * (g->dir.y * pos.x - g->dir.x * pos.y);
		sp->trans.y = inv_det * (-g->plane.y * pos.x + g->plane.x * pos.y);
	}
}
