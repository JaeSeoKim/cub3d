/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lifebar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 01:32:26 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 00:56:27 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	int		i;
	t_img	*img;
	t_vec	size;
	t_vec	start;

	img = &g->assets[LIFEBAR];
	size = new_vec(g->v.w / 3, g->v.w / 3 * img->h / img->w);
	start = new_vec(g->v.w - g->v.w / 100 - size.x, g->v.h / 50);
	put_img(g, size.x, start, img);
	render_life_gauge(g, size, start);
	start.y += size.y;
	start.x = g->v.w - 1;
	i = -1;
	while (++i < 4)
	{
		start.x -= g->v.w / 20 + g->v.w / 50;
		if (g->poke[i])
			put_img(g, g->v.w / 20, start, g->poke[i]);
	}
}
