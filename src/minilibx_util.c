/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:22:18 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/03 17:20:30 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define _USE_MATH_DEFINES
#include <math.h>

t_uc	g_no_stroke = 0;
t_ui	g_stroke = 0x00000000;
t_ui	g_fill = 0x00000000;

int		calc_rgba(t_ui background, t_ui color)
{
	t_ui	result;
	float	alpha;

	alpha = ((255 - (color >> 24 & 255)) / 255.0f);
	result = 0;
	result |= (t_ui)((1 - alpha) * (background >> 16 & 255) \
				+ alpha * (color >> 16 & 255)) << 16;
	result |= (t_ui)((1 - alpha) * (background >> 8 & 255) \
				+ alpha * (color >> 8 & 255)) << 8;
	result |= (t_ui)((1 - alpha) * (background & 255) + alpha * (color & 255));
	return (result);
}

void	line(t_img *view, t_vec a, t_vec b)
{
	long	distance;
	int		index;
	float	rad;
	t_vec	vec;

	rad = atan2f(b.y - a.y, b.x - a.x);
	distance = (long)sqrtf((b.x - a.x) * (b.x - a.x) + \
							(b.y - a.y) * (b.y - a.y));
	vec.x = cos(rad);
	vec.y = sin(rad);
	while (distance > 0)
	{
		index = (int)(a.y + vec.y * distance) * view->line + \
					(int)(a.x + vec.x * distance);
		view->data[index] = calc_rgba(view->data[index], g_stroke);
		--distance;
	}
}

// void	rect(t_img *view, t_vec position, int width, int height)
// {
// 	int		index;
// 	int		i;
// 	int		j;
// 	t_vec	vec;

// 	vec.x = position.x - (width / 2);
// 	vec.y = position.y - (height / 2);
// 	i = 0;
// 	while (i < width)
// 	{
// 		j = 0;
// 		while (j < height)
// 		{
// 			index = (((int)vec.y + j++) * view->line) \
// 						+ (int)vec.x + i;
// 			view->data[index] = calc_rgba(view->data[index], g_fill);
// 		}
// 		++i;
// 	}
// }

void	rect(t_img *view, t_vec position, int width, int height)
{
	int		color;
	int		index;
	int		i;
	int		j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			index = (((int)position.y + j++) * view->line) \
						+ (int)position.x + i;
			color = (g_no_stroke == 0 && (i == 0 || i == width - 1 || \
					j == 1 || j == height)) ? g_stroke : g_fill;
			view->data[index] = calc_rgba(view->data[index], color);
		}
		++i;
	}
}

void	fill(int color)
{
	g_fill = color;
}

void	fill_rgba(t_uc r, t_uc g, t_uc b, t_uc a)
{
	g_fill = 0;
	g_fill |= ((int)(255 - a) << 24);
	g_fill |= (r << 16);
	g_fill |= (g << 8);
	g_fill |= b;
}

void	no_stroke()
{
	g_no_stroke = 1;
}

void	stroke(int color)
{
	g_no_stroke = 0;
	g_stroke = color;
}

void	stroke_rgba(t_uc r, t_uc g, t_uc b, t_uc a)
{
	g_no_stroke = 0;
	g_stroke = 0;
	g_stroke |= ((int)(255 - a) << 24);
	g_stroke |= (r << 16);
	g_stroke |= (g << 8);
	g_stroke |= b;
}
