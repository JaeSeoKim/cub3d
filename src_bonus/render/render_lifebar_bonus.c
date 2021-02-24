/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lifebar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 01:32:26 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/25 04:09:19 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_life_asset(t_cub3d *g, t_vec size, t_vec start)
{
	t_ivec	iv;
	t_img	*img;
	t_vec	step;

	img = &g->assets[LIFEBAR];
	step = new_vec(img->w / size.x, img->h / size.y);
	iv.x = -1;
	while (++iv.x < size.x)
	{
		iv.y = -1;
		while (++iv.y < size.y)
		{
			g_color = img->data[
				(int)(step.y * iv.y) * img->line + (int)(step.x * iv.x)];
			put_pixel(&g->v, start.x + iv.x, start.y + iv.y);
		}
	}
}

void	render_life_gauge(t_cub3d *g, t_vec size, t_vec start)
{
	t_img	*img;

	img = &g->assets[LIFEBAR];
	if (g->life > 50)
		g_color = rgba(0, 255, 0, 1);
	else if (g->life > 25)
		g_color = rgba(255, 140, 0, 1);
	else
		g_color = rgba(255, 66, 0, 1);
	rect(&g->v, new_vec(start.x + size.x / img->w * LIFEBAR_START_X,
						start.y + size.y / img->h * LIFEBAR_START_Y),
		size.x / img->w * LIFEBAR_SIZE_X / 100 * g->life,
		size.y / img->h * LIFEBAR_SIZE_Y);
}

void	render_lifebar(t_cub3d *g)
{
	t_img	*img;
	t_vec	size;
	t_vec	start;
	t_vec	step;

	img = &g->assets[LIFEBAR];
	size = new_vec(g->v.w / 3, g->v.w / 3 * img->h / img->w);
	start = new_vec(g->v.w - g->v.w / 100 - size.x, g->v.h / 50);
	render_life_asset(g, size, start);
	render_life_gauge(g, size, start);
}
