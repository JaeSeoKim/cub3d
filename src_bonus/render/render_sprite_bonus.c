/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:18:54 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 00:10:39 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_ivec	nor_sp_size(t_sprite *sp, t_ivec size, t_ivec pos)
{
	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > size.x)
		pos.x = size.x - 1;
	if (pos.y < -sp->move_y)
		pos.y = -sp->move_y;
	else if (pos.y > size.y)
		pos.y = size.y - 1;
	return (pos);
}

static void		put_sprite_pixel(
	t_cub3d *g,
	t_sprite *sp,
	int dist,
	t_ivec iv)
{
	if (g_color.bit.t != 255)
	{
		g_color = calc_rgba(g_color, rgba(0, 0, 0, g->shadow / dist));
		put_pixel(&g->v, iv.x, iv.y + sp->move_y);
	}
}

static void		render_sprite_tex(
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
	start.y = -size.y / 2 + g->v.h / 2;
	end.y = size.y / 2 + g->v.h / 2;
	start = nor_sp_size(sp, new_ivec(g->v.w, g->v.h + sp->move_y), start);
	end = nor_sp_size(sp, new_ivec(g->v.w, g->v.h - sp->move_y), end);
	iv.x = start.x - 1;
	while (++iv.x < end.x)
	{
		tex.x = ((iv.x - (-size.x / 2 + move.x)) * sp->tex->w / size.x);
		iv.y = (iv.x > 0 && iv.x < g->v.w && sp->trans.y
			< g->rays[iv.x / WALL_STRIP_WIDTH].dist ? start.y - 1 : end.y);
		while (++iv.y < end.y)
		{
			tex.y = (iv.y - move.y) * 256 - g->v.h * 128 + size.y * 128;
			tex.y = ((tex.y * sp->tex->h) / size.y) / 256;
			g_color = sp->tex->data[sp->tex->line * tex.y + tex.x];
			put_sprite_pixel(g, sp, size.y, iv);
		}
	}
}

void			render_sprite(t_cub3d *g)
{
	t_list		*curr;
	t_ivec		move;
	t_ivec		size;
	t_sprite	*sp;

	curr = g->sp;
	while (curr)
	{
		sp = curr->content;
		move.x = ((g->v.w / 2) * (1 + sp->trans.x / sp->trans.y));
		move.y = (V_MOVE / sp->trans.y);
		size.x = fabs((g->fov_h / sp->trans.y) / U_DIV);
		size.y = fabs((g->fov_h / sp->trans.y) / V_DIV);
		sp->move_y = g->dir_z - ((int)g->count % 2 == 0 && \
			ft_strchr(S_J, sp->base) ? size.y / 10 : 0);
		if (sp->trans.y > 0)
			render_sprite_tex(g, sp, size, move);
		curr = curr->next;
	}
}
