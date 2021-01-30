/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:18:54 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/31 00:29:10 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	(start.x < 0 ? start.x = 0 : 0);
	end.x = size.x / 2 + move.x;
	(end.x > g->v.width ? end.x = g->v.width - 1 : 0);

	start.y = -size.y / 2 + g->v.height / 2;
	(start.y < 0 ? start.y = 0 : 0);
	end.y = size.y / 2 + g->v.height / 2;
	(end.y > g->v.height ? end.y = g->v.height - 1 : 0);
	iv.x = start.x - 1;
	while (++iv.x < end.x)
	{
		tex.x = (int)(256 * (iv.x - (-size.x / 2 + move.x)) * sp->tex->width / size.x) / 256;
		iv.y = (sp->trans.y > 0 && iv.x > 0 && iv.x < g->v.width && sp->trans.y
			< g->rays[iv.x].dist ? start.y - 1 : end.y + 1);
		while (++iv.y < end.y)
		{
			tex.y = (iv.y - move.y) * 256 - g->v.height * 128 + size.y * 128;
			tex.y = ((tex.y * sp->tex->height) / size.y) / 256;
			g_color = sp->tex->data[sp->tex->line * tex.y + tex.x];
			if (g_color.bit.t != 255)
				put_pixel(&g->v, iv.x, iv.y);
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
