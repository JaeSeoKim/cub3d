/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 21:14:14 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/26 13:36:35 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color		g_color = (t_color)0x00000000;

void	color_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	if (a > 1)
		a = 1;
	g_color.bit.t = 255 - a * 255;
	g_color.bit.r = r;
	g_color.bit.g = g;
	g_color.bit.b = b;
}

t_color	rgba(t_uc r, t_uc g, t_uc b, float a)
{
	t_color		color;

	if (a > 1)
		a = 1;
	color.bit.t = 255 - a * 255;
	color.bit.r = r;
	color.bit.g = g;
	color.bit.b = b;

	return (color);
}
