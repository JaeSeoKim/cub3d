/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:26:11 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/28 21:46:36 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_wall_texture(t_cub3d *g, t_ray *ray, t_vec pos, int wall_h)
{
	int		i;
	int		y;
	float	step;
	t_vec	tex_p;

	tex_p.x = ray->side ? \
		g->pos.x + ray->dist * ray->dir.x :
		g->pos.y + ray->dist * ray->dir.y;
	tex_p.x = (int)((tex_p.x - floor(tex_p.x)) * ray->tex->width);
	if ((!ray->side && ray->dir.x < 0) || (ray->side && ray->dir.y > 0))
		tex_p.x = ray->tex->width - tex_p.x - 1;
	step = (float)ray->tex->height / wall_h;
	(pos.y < 0 ? (pos.y = 0) : 0);
	tex_p.y = (pos.y - g->v.height / 2 + wall_h / 2) * step;
	(wall_h > g->v.height ? (wall_h = g->v.height - 1) : 0);
	i = 0;
	while (i < wall_h)
	{
		y = ((int)tex_p.y & ray->tex->height - 1);
		g_color = ray->tex->data[y * ray->tex->line + (int)tex_p.x];
		put_pixel(&g->v, pos.x, pos.y + i);
		tex_p.y += step;
		i++;
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

void	render(t_cub3d *g)
{
	render_wall(g);
}
