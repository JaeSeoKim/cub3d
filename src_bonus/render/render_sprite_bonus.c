/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:18:54 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 17:26:17 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		render_sprite_tex(
	t_cub3d *g,
	t_sprite *sp,
	t_ivec size,
	t_ivec move)
{
	t_ivec	iv;
	t_ivec	tex;
	t_ivec	start;
	t_ivec	end;

	start.x = -size.x / 2 + move.x;
	end.x = size.x / 2 + move.x;
	start.y = -size.y / 2 + g->v.height / 2;
	end.y = size.y / 2 + g->v.height / 2;
	normalise_ipos(g, &start);
	normalise_ipos(g, &end);
	iv.x = start.x - 1;
	while (++iv.x < end.x)
	{
		tex.x = ((iv.x - (-size.x / 2 + move.x)) * sp->tex->width / size.x);
		iv.y = (sp->trans.y > 0 && iv.x > 0 && iv.x < g->v.width && sp->trans.y
			< g->rays[iv.x / WALL_STRIP_WIDTH].dist ? start.y - 1 : end.y);
		while (++iv.y < end.y)
		{
			tex.y = (iv.y - move.y) * 256 - g->v.height * 128 + size.y * 128;
			tex.y = ((tex.y * sp->tex->height) / size.y) / 256;
			g_color = sp->tex->data[sp->tex->line * tex.y + tex.x];
			(g_color.bit.t != 255 ? put_pixel(&g->v, iv.x, iv.y) : 0);
		}
	}
}

void		render_sprite(t_cub3d *g)
{
	int			i;
	t_ivec		move;
	t_ivec		size;
	t_sprite	*sp;

	i = -1;
	while (++i < g->num_sp)
	{
		sp = &g->sp[g->sp_order[i]];
		move.x = (int)((g->v.width / 2) * (1 + sp->trans.x / sp->trans.y));
		move.y = (int)(V_MOVE / sp->trans.y);
		size.x = (int)fabs((g->fov_h / sp->trans.y) / U_DIV);
		size.y = (int)fabs((g->fov_h / sp->trans.y) / V_DIV);
		render_sprite_tex(g, sp, size, move);
	}
}
