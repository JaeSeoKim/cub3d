/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 21:14:14 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/16 21:01:28 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_color = 0x00000000;
int		g_stroke = 0x00000000;
int		g_fill = 0x00000000;
int		g_no_stroke = 0;

void	fill_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	g_fill = 0;
	g_fill |= ((t_uc)(255 - a * 255) << 24);
	g_fill |= (r << 16);
	g_fill |= (g << 8);
	g_fill |= b;
}

void	no_stroke(void)
{
	g_no_stroke = 1;
}

void	stroke_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	g_no_stroke = 0;
	g_stroke = 0;
	g_stroke |= ((t_uc)(255 - a * 255) << 24);
	g_stroke |= (r << 16);
	g_stroke |= (g << 8);
	g_stroke |= b;
}

void	color_rgba(t_uc r, t_uc g, t_uc b, float a)
{
	g_color = 0;
	g_color |= ((t_uc)(255 - a * 255) << 24);
	g_color |= (r << 16);
	g_color |= (g << 8);
	g_color |= b;
}

int		rgba(t_uc r, t_uc g, t_uc b, float a)
{
	int		color;

	color = 0;
	color |= ((t_uc)(255 - a * 255) << 24);
	color |= (r << 16);
	color |= (g << 8);
	color |= b;

	return (color);
}
