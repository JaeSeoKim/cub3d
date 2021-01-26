/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:22:18 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/26 16:14:59 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	calc_rgba(t_color background, t_color color)
{
	float	alpha;
	t_color	result;

	if (color.bit.t == 0)
		return (color);
	alpha = ((255 - (color.bit.t)) / 255.0);
	result.i = 0;
	result.bit.r = ((1 - alpha) * (background.bit.r) \
				+ alpha * (color.bit.r));
	result.bit.g = ((1 - alpha) * (background.bit.g) \
				+ alpha * (color.bit.g));
	result.bit.b = ((1 - alpha) * (background.bit.b) \
				+ alpha * (color.bit.b));
	return (result);
}

void	put_pixel(t_img *view, int x, int y)
{
	int	index;

	index = y * view->line + x;
	view->data[index] = calc_rgba(view->data[index], g_color);
}
