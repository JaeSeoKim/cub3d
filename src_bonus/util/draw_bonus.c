/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:07:08 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 04:16:50 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		line(t_img *view, t_vec a, t_vec b)
{
	long	distance;
	float	rad;

	rad = atan2f(b.y - a.y, b.x - a.x);
	distance = (long)sqrtf((b.x - a.x) * (b.x - a.x) + \
							(b.y - a.y) * (b.y - a.y));
	b.x = cos(rad);
	b.y = sin(rad);
	while (distance > 0)
	{
		a.x += b.x;
		a.y += b.y;
		put_pixel(view, a.x, a.y);
		--distance;
	}
}

void		rect(t_img *view, t_vec position, int width, int height)
{
	t_ivec	vec;
	int		i;
	int		j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			vec.x = position.x + i;
			vec.y = position.y + j++;
			put_pixel(view, vec.x, vec.y);
		}
		++i;
	}
}

void		mid_point_rect(t_img *view, t_vec position, int width, int height)
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
			put_pixel(view, vec.x, vec.y);
		}
		++i;
	}
}

void		put_pixel(t_img *view, int x, int y)
{
	int	index;

	if (0 <= x && x < view->w && 0 <= y && y < view->h)
	{
		index = y * view->line + x;
		view->data[index] = calc_rgba(view->data[index], g_color);
	}
}
