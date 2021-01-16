/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:22:18 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/16 21:08:08 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calc_rgba(int background, int color)
{
	int		transparent;
	int		result;
	float	alpha;

	if ((transparent = color >> 24 & 255) == 0)
		return (color);
	alpha = ((255 - (transparent)) / 255.0f);
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

	if (0 <= x && x < 512 && 0 <= y && y < 512)
	{
		index = y * view->line + x;
		view->data[index] = calc_rgba(view->data[index], g_color);
	}
}

// void	ft_int_swap(int *a, int *b)
// {
// 	int		tmp;

// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// void	line(t_img *view, t_vec a, t_vec b)
// {
// 	t_ivec	d;
// 	t_ivec	tmp;
// 	int		pixel;
// 	int		distance;
// 	int		flag;

// 	g_color = g_stroke;
// 	d.x = fabs(b.x - a.x);
// 	d.y = fabs(b.y - a.y);
// 	flag = d.x < d.y;
// 	distance = flag ? d.y : d.x;
// 	tmp.x = a.x < b.x ? 1 : -1;
// 	tmp.y = a.y < b.y ? 1 : -1;
// 	(flag ? ft_int_swap(&d.x, &d.y) : NULL);
// 	pixel = 2 * (d.y - d.x);

// 	while (distance-- > 0)
// 	{
// 		put_pixel(view, a.x, a.y);
// 		if (pixel > 0 && ((pixel += 2 * (d.y - d.x)) || 1))
// 			(flag ? (a.x += tmp.x) : (a.y += tmp.y));
// 		else
// 			pixel += 2 * d.y;
// 		(flag ? (a.y += tmp.y) : (a.x += tmp.x));
// 	}
// }
