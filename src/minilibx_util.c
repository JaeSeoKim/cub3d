/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:22:18 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/01 00:47:38 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define _USE_MATH_DEFINES
#include <math.h>

int		g_stroke = 0x00000000;
int		g_fill = 0x00000000;

void	line(t_img *view, t_vec a, t_vec b)
{
	long	distance;
	float	rad;
	float	x;
	float	y;

	rad = atan2f(b.y - a.y, b.x - a.x);
	distance = (long)sqrtf((b.x - a.x) * (b.x - a.x) + \
							(b.y - a.y) * (b.y - a.y));
	x = cos(rad);
	y = sin(rad);
	while (distance > 0)
	{
		view->data[(int)(a.y + y * distance) * view->line + \
					(int)(a.x + x * distance)] = 0x0000FF00;
		--distance;
	}
}

// void	rect(t_img *view, t_vec position, int width, int height)
// {

// }

void	fill(int color)
{
	g_fill = color;
}

void	stroke(int color)
{
	g_stroke = color;
}
