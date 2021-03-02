/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:47:22 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 00:50:36 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_img(t_cub3d *g, float size_x, t_vec start, t_img *img)
{
	float	size_y;
	t_ivec	iv;
	t_vec	step;

	size_y = size_x * img->h / img->w;
	step = new_vec(img->w / size_x, img->h / size_y);
	iv.x = -1;
	while (++iv.x < size_x)
	{
		iv.y = -1;
		while (++iv.y < size_y)
		{
			g_color = img->data[
				(int)(step.y * iv.y) * img->line + (int)(step.x * iv.x)];
			put_pixel(&g->v, start.x + iv.x, start.y + iv.y);
		}
	}
}
