/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:22:18 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/17 08:22:37 by jaeskim          ###   ########.fr       */
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

	index = y * view->line + x;
	view->data[index] = g_color;
}
