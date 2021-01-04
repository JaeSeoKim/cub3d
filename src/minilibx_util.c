/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:22:18 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/04 21:44:26 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define _USE_MATH_DEFINES
#include <math.h>

int		g_color = 0x00000000;
int		g_stroke = 0x00000000;
int		g_fill = 0x00000000;
int		g_no_stroke = 0;

int		calc_rgba(int background, int color)
{
	int		result;
	float	alpha;

	alpha = ((255 - (color >> 24 & 255)) / 255.0f);
	result = 0;
	result |= (int)((1 - alpha) * (background >> 16 & 255) \
				+ alpha * (color >> 16 & 255)) << 16;
	result |= (int)((1 - alpha) * (background >> 8 & 255) \
				+ alpha * (color >> 8 & 255)) << 8;
	result |= (int)((1 - alpha) * (background & 255) + alpha * (color & 255));
	return (result);
}

void	put_pixel(t_img *view, int x, int y)
{
	int	index;

	index = y * view->line + x;
	view->data[index] = calc_rgba(view->data[index], g_color);
}

void	ft_int_swap(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	line(t_img *view, t_vec a, t_vec b)
{
	t_ivec	d;
	t_ivec	tmp;
	int		pixel;
	int		distance;
	int		flag;

	g_color = g_stroke;
	d.x = abs((int)(b.x - a.x));
	d.y = abs((int)(b.y - a.y));
	flag = d.x < d.y;
	distance = flag ? d.y : d.x;
	tmp.x = a.x < b.x ? 1 : -1;
	tmp.y = a.y < b.y ? 1 : -1;
	(flag ? ft_int_swap(&d.x, &d.y) : NULL);
	pixel = 2 * (d.y - d.x);
	while (distance-- > 0)
	{
		put_pixel(view, a.x, a.y);
		if (pixel >= 0 && ((pixel += 2 * (d.y - d.x)) || 1))
			(flag ? (a.x += tmp.x) : (a.y += tmp.y));
		else
			pixel += 2 * d.y;
		(flag ? (a.y += tmp.y) : (a.x += tmp.x));
	}
}

void	rect(t_img *view, t_vec position, int width, int height)
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

void	fill(int color)
{
	g_fill = color;
}

void	fill_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	g_fill = 0;
	g_fill |= ((t_uc)(a / 255) << 24);
	g_fill |= (r << 16);
	g_fill |= (g << 8);
	g_fill |= b;
}

void	no_stroke(void)
{
	g_no_stroke = 1;
}

void	stroke(int color)
{
	g_no_stroke = 0;
	g_stroke = color;
}

void	stroke_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	g_no_stroke = 0;
	g_stroke = 0;
	g_stroke |= ((t_uc)(a / 255) << 24);
	g_stroke |= (r << 16);
	g_stroke |= (g << 8);
	g_stroke |= b;
}

void	color_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	g_color = 0;
	g_color |= ((t_uc)(a / 255) << 24);
	g_color |= (r << 16);
	g_color |= (g << 8);
	g_color |= b;
}
