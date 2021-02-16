/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:41:26 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 21:25:08 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	render_wall_texture(t_cub3d *g, t_ray *ray, t_vec pos, int wall_h)
{
	int		y;
	t_ivec	iv;
	float	step;
	t_vec	tex_p;

	tex_p.x = ray->side ? g->pos.x + ray->dist * ray->dir.x :
		g->pos.y + ray->dist * ray->dir.y;
	tex_p.x = (int)((tex_p.x - floor(tex_p.x)) * ray->tex->width);
	if ((!ray->side && ray->dir.x < 0) || (ray->side && ray->dir.y > 0))
		tex_p.x = ray->tex->width - tex_p.x - 1;
	step = (float)ray->tex->height / wall_h;
	(pos.y < 0 ? (pos.y = 0) : 0);
	tex_p.y = (pos.y - g->v.height / 2 + wall_h / 2) * step;
	(wall_h > g->v.height ? (wall_h = g->v.height - 1) : 0);
	iv.y = -1;
	while (++iv.y < wall_h)
	{
		y = ((int)tex_p.y & ray->tex->height - 1);
		g_color = ray->tex->data[y * ray->tex->line + (int)tex_p.x];
		g_color = calc_rgba(g_color, rgba(0, 0, 0, 30.0 / wall_h));
		iv.x = -1;
		while (++iv.x < WALL_STRIP_WIDTH)
			put_pixel(&g->v, pos.x + iv.x, pos.y + iv.y);
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
		pos.y = g->v.height / 2 - wall_h / 2;
		render_wall_texture(g, &g->rays[i], pos, wall_h);
	}
}
