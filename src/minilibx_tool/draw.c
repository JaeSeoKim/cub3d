/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:07:08 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/26 21:28:06 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_int_swap(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		line(t_img *view, t_vec a, t_vec b)
{
	t_ivec	d;
	t_ivec	tmp;
	int		pixel;
	int		distance;
	int		flag;

	d.x = fabs(b.x - a.x);
	d.y = fabs(b.y - a.y);
	flag = d.x < d.y;
	distance = flag ? d.y : d.x;
	tmp.x = a.x < b.x ? 1 : -1;
	tmp.y = a.y < b.y ? 1 : -1;
	(flag ? ft_int_swap(&d.x, &d.y) : NULL);
	pixel = 2 * (d.y - d.x);

	while (distance-- > 0)
	{
		put_pixel(view, a.x, a.y);
		if (pixel > 0 && ((pixel += 2 * (d.y - d.x)) || 1))
			(flag ? (a.x += tmp.x) : (a.y += tmp.y));
		else
			pixel += 2 * d.y;
		(flag ? (a.y += tmp.y) : (a.x += tmp.x));
	}
}

// void	line(t_img *view, t_vec a, t_vec b)
// {
// 	long	distance;
// 	float	rad;

// 	rad = atan2f(b.y - a.y, b.x - a.x);
// 	distance = (long)sqrtf((b.x - a.x) * (b.x - a.x) + \
// 							(b.y - a.y) * (b.y - a.y));
// 	b.x = cos(rad);
// 	b.y = sin(rad);

// 	g_color = g_stroke;
// 	while (distance > 0)
// 	{
// 		a.x += b.x;
// 		a.y += b.y;
// 		put_pixel(view, a.x, a.y);
// 		--distance;
// 	}
// }

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
