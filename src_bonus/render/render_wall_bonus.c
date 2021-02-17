/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:41:26 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/17 22:36:50 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	put_wall_pixel(t_cub3d *g, t_ivec iv, t_vec pos)
{
	iv.x = -1;
	while (++iv.x < WALL_STRIP_WIDTH)
		put_pixel(&g->v, pos.x + iv.x, pos.y + iv.y);
}

static void	render_wall_texture(t_cub3d *g, t_ray *ray, t_vec pos, int wall_h)
{
	t_ivec	iv;
	float	alpha;
	float	step;
	t_vec	tex_p;

	tex_p.x = ray->side ? g->pos.x + ray->dist * ray->dir.x :
		g->pos.y + ray->dist * ray->dir.y;
	tex_p.x = (int)((tex_p.x - floor(tex_p.x)) * ray->tex->w);
	if ((!ray->side && ray->dir.x < 0) || (ray->side && ray->dir.y > 0))
		tex_p.x = ray->tex->w - tex_p.x - 1;
	step = (float)ray->tex->h / wall_h;
	tex_p.y = (nor_pos(g, pos).y - g->v.h / 2 + wall_h / 2 - g->dir_z) * step;
	alpha = g->shadow / wall_h;
	(pos.y < 0 && (wall_h += pos.y) ? (pos.y = 0) : 0);
	(wall_h > g->v.h ? (wall_h = g->v.h - 1) : 0);
	iv.y = -1;
	while (++iv.y < wall_h)
	{
		g_color = ray->tex->data[((int)tex_p.y & ray->tex->h - 1)
			* ray->tex->line + (int)tex_p.x];
		g_color = calc_rgba(g_color, rgba(0, 0, 0, alpha));
		put_wall_pixel(g, iv, pos);
		tex_p.y += step;
	}
}

void		render_wall(t_cub3d *g)
{
	int		i;
	int		wall_h;
	t_vec	pos;

	i = -1;
	while (++i < g->num_rays)
	{
		wall_h = g->fov_h / g->rays[i].dist;
		pos.x = i * WALL_STRIP_WIDTH;
		pos.y = g->v.h / 2 - wall_h / 2 + g->dir_z;
		render_wall_texture(g, &g->rays[i], pos, wall_h);
	}
}
