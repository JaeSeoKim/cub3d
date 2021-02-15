/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_all_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:36:49 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/15 23:02:40 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_ray(t_cub3d *g, t_ray *ray)
{
	t_vec	side_d;
	t_vec	delta_d;
	t_ivec	step;
	int		hit;

	delta_d.x = fabsf(1 / ray->dir.x);
	delta_d.y = fabsf(1 / ray->dir.y);
	step = new_ivec(ray->dir.x < 0 ? -1 : 1, ray->dir.y < 0 ? -1 : 1);
	side_d.x = ray->dir.x < 0 ? (g->pos.x - ray->map.x) * delta_d.x :
				(ray->map.x + 1.0 - g->pos.x) * delta_d.x;
	side_d.y = ray->dir.y < 0 ? (g->pos.y - ray->map.y) * delta_d.y :
				(ray->map.y + 1.0 - g->pos.y) * delta_d.y;
	hit = 0;
	while (!hit)
	{
		if (side_d.x < side_d.y && !(ray->side = 0))
			((side_d.x += delta_d.x) || 1 ? (ray->map.x += step.x) : 0);
		else if ((ray->side = 1))
			((side_d.y += delta_d.y) || 1 ? (ray->map.y += step.y) : 0);
		(g->map.data[ray->map.y][ray->map.x] == '1' ? hit = 1 : 0);
	}
	ray->dist = (ray->side ?
		(ray->map.y - g->pos.y + (1 - step.y) / 2) / ray->dir.y :
		(ray->map.x - g->pos.x + (1 - step.x) / 2) / ray->dir.x);
}

void		update_all_rays(t_cub3d *g)
{
	int		i;
	int		tex_i;
	float	camera_x;

	i = -1;
	while (++i < g->num_rays)
	{
		camera_x = 2 * (i * WALL_STRIP_WIDTH) / (float)g->v.width - 1;
		ft_memset(&g->rays[i], 0, sizeof(t_ray));
		g->rays[i].dir.x = g->dir.x + g->plane.x * camera_x;
		g->rays[i].dir.y = g->dir.y + g->plane.y * camera_x;
		g->rays[i].map = new_ivec(g->pos.x, g->pos.y);
		cast_ray(g, &g->rays[i]);
		if (g->rays[i].side)
			tex_i = g->rays[i].dir.y < 0 ? NO : SO;
		else
			tex_i = g->rays[i].dir.x < 0 ? EA : WE;
		g->rays[i].tex = &g->tex[tex_i];
	}
}
