/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:07:08 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/16 21:01:30 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	line(t_img *view, t_vec a, t_vec b)
{
	long	distance;
	float	rad;

	rad = atan2f(b.y - a.y, b.x - a.x);
	distance = (long)sqrtf((b.x - a.x) * (b.x - a.x) + \
							(b.y - a.y) * (b.y - a.y));
	b.x = cos(rad);
	b.y = sin(rad);

	g_color = g_stroke;
	while (distance > 0)
	{
		a.x += b.x;
		a.y += b.y;
		put_pixel(view, a.x, a.y);
		--distance;
	}
}

void	rect(t_img *view, t_vec position, int width, int height)
{
	t_ivec	vec;
	int		i;
	int		j;

	i = 0;
	position.x = position.x < 0 ? 0 : position.x;
	position.y = position.y < 0 ? 0 : position.y;
	while (i < width && (position.x + i) < 512)
	{
		j = 0;
		while (j < height && (position.y + j) < 512)
		{
			vec.x = position.x + i;
			vec.y = position.y + j++;
			g_color = (g_no_stroke == 0 && (i == 0 || i == width - 1 || \
					j == 1 || j == height)) ? g_stroke : g_fill;
			put_pixel(view, vec.x, vec.y);
		}
		++i;
	}
}

void	mid_point_rect(t_img *view, t_vec position, int width, int height)
{
	t_ivec	vec;
	int		i;
	int		j;

	position.x -= width / 2;
	position.y -= height / 2;
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			vec.x = position.x + i;
			vec.y = position.y + j++;
			g_color = (g_no_stroke == 0 && (i == 0 || i == width - 1 || \
					j == 1 || j == height)) ? g_stroke : g_fill;
			put_pixel(view, vec.x, vec.y);
		}
		++i;
	}
}
