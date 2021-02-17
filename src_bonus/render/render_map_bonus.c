/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:57:55 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/17 14:51:45 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	render_plane_map(t_cub3d *g, int size)
{
	int		i;
	t_vec	hit;

	g_color = rgba(255, 123, 123, 1);
	i = 0;
	while (i < g->num_rays)
	{
		hit = new_vec(size / 2 + g->rays[i].dir.x * size / 2,
					size / 2 + g->rays[i].dir.y * size / 2);
		(hit.x < 0 ? hit.x = 0 : 0);
		(hit.y < 0 ? hit.y = 0 : 0);
		(hit.x > size ? hit.x = size : 0);
		(hit.y > size ? hit.y = size : 0);
		line(&g->v, new_vec(size / 2, size / 2), hit);
		i += g->num_rays / size;
	}
}

static void	render_tile_map(t_cub3d *g, int size, t_vec obj, float step)
{
	t_ivec	iv;

	iv.y = -1;
	while (++iv.y < size)
	{
		obj.x = g->pos.x - 5;
		iv.x = -1;
		while (++iv.x < size)
		{
			if (0 <= obj.x && obj.x < g->map.w &&
				0 <= obj.y && obj.y < g->map.h)
			{
				if (g->map.data[(int)(obj.y)][(int)obj.x] == '1')
					g_color = rgba(123, 123, 123, 0.5);
				else if (g->map.data[(int)obj.y][(int)obj.x] == '2')
					g_color = rgba(123, 255, 123, 0.5);
				else
					g_color = rgba(12, 12, 12, 0.5);
				put_pixel(&g->v, iv.x, iv.y);
			}
			obj.x += step;
		}
		obj.y += step;
	}
}

void		render_map(t_cub3d *g)
{
	int		size;
	float	step;
	t_vec	obj;

	size = g->v.height > g->v.width ?
		g->v.width / g->map_size : g->v.height / g->map_size;
	obj = new_vec(g->pos.x - 5, g->pos.y - 5);
	step = ((g->pos.x + 5) - obj.x) / size;
	g_color = rgba(200, 200, 200, 1);
	render_plane_map(g, size);
	render_tile_map(g, size, obj, step);
	g_color = rgba(255, 123, 123, 1);
	mid_point_rect(&g->v, new_vec(size / 2, size / 2), size / 15, size / 15);
}
