/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:26:11 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/26 21:52:14 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall(t_cub3d *g)
{
	int		i;
	int		wall_h;
	t_vec	pos;

	i = -1;
	while (++i < g->num_rays)
	{
		wall_h = g->v.width / 2 / tan(g->fov / 2) / g->rays[i].dist;
		pos.x = i * WALL_STRIP_WIDTH;
		pos.y = g->v.height / 2 - wall_h / 2;
		(pos.y < 0 ? (pos.y = 0) : 0);
		(wall_h > g->v.height ? (wall_h = g->v.height - 1) : 0);
		color_rgba(g->rays[i].side ? 200 : 255, 0, 0, 1);
		rect(&g->v, pos, WALL_STRIP_WIDTH, wall_h);
	}
}

void	render(t_cub3d *g)
{
	render_wall(g);
}
