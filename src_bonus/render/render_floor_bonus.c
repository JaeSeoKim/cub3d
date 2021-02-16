/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:38:28 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 18:55:53 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_floor(t_cub3d *g)
{
	float	dist;
	t_vec	obj;
	t_vec	step;
	t_ivec	iv[2];

	iv[0].y = -1;
	while (++iv[0].y < g->v.height / 2)
	{
		dist = fabs(0.5 * g->fov_h / (iv[0].y - g->v.height / 2));
		obj.x = g->pos.x + g->dir_plane.x * dist;
		obj.y = g->pos.y + g->dir_plane.y * dist;
		step.x = ((g->dir.x + g->plane.x) - g->dir_plane.x) * dist / g->v.width;
		step.y = ((g->dir.y + g->plane.y) - g->dir_plane.y) * dist / g->v.width;
		iv[0].x = -1;
		while (++iv[0].x < g->v.width)
		{
			iv[1].x = g->tex[F].width * (obj.x - floor(obj.x));
			iv[1].y = g->tex[F].height * (obj.y - floor(obj.y));
			g_color = g->tex[F].data[iv[1].y * g->tex[F].line + iv[1].x];
			put_pixel(&g->v, iv[0].x, g->v.height - 1 - iv[0].y);
			obj.x += step.x;
			obj.y += step.y;
		}
	}
}
