/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:26:06 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/26 21:59:49 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player(t_cub3d *g)
{
	int		walk_dir;
	int		turn_dir;
	t_vec	new_pos;

	turn_dir = g->key.a ? -1 : 0;
	turn_dir += g->key.d ? 1 : 0;
	walk_dir = g->key.w ? 1 : 0;
	walk_dir += g->key.s ? -1 : 0;

	g->dir = rot_vec(g->dir, turn_dir * TURN_S * M_PI_180);
	g->plane = rot_vec(g->plane, turn_dir * TURN_S * M_PI_180);

	if (walk_dir != 0)
	{
		new_pos.x = g->pos.x + g->dir.x * (walk_dir * WALK_S);
		new_pos.y = g->pos.y + g->dir.y * (walk_dir * WALK_S);
		if (!g->map.data[
			(int)g->pos.y * g->map.width + (int)new_pos.x])
			g->pos.x = new_pos.x;
		if (!g->map.data[
			(int)new_pos.y * g->map.width + (int)g->pos.x])
			g->pos.y = new_pos.y;
	}
}

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
		(g->map.data[ray->map.y * g->map.width + ray->map.x] > 0 ? hit = 1 : 0);
	}
	ray->dist = (ray->side ?
		(ray->map.y - g->pos.y + (1 - step.y) / 2) / ray->dir.y :
		(ray->map.x - g->pos.x + (1 - step.x) / 2) / ray->dir.x);
}

static void	cast_all_rays(t_cub3d *g)
{
	int		i;
	float	camera_x;

	i = -1;
	while (++i < g->num_rays)
	{
		camera_x = 2 * (i * WALL_STRIP_WIDTH) / (float)g->v.width - 1;
		ft_memset(&g->rays[i], 0, sizeof(t_ray));
		g->rays[i].dir.x = g->dir.x + g->plane.x * camera_x;
		g->rays[i].dir.y = g->dir.y + g->plane.y * camera_x;
		g->rays[i].map = new_ivec(g->pos.x, g->pos.y);
		g->rays[i].cp |= g->rays[i].dir.x < 0 ? 1 << NO : 1 << SO;
		g->rays[i].cp |= g->rays[i].dir.y < 0 ? 1 << WE : 1 << EA;
		cast_ray(g, &g->rays[i]);
	}
}

void		update(t_cub3d *g)
{
	update_player(g);
	cast_all_rays(g);
}
