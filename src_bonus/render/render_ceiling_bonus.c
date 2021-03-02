/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:38:28 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 06:44:26 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_ceiling(t_cub3d *g)
{
	int		tex_x;
	t_vec	size;
	t_ivec	iv;
	t_vec	step;
	float	degree;

	size.x = g->v.w;
	size.y = g->v.h;
	step = new_vec(g->tex[C].w / size.x / 4, g->tex[C].h / size.y);
	iv.x = -1;
	degree = atan2f(g->dir.y, g->dir.x) * 180 / M_PI;
	while (++iv.x < size.x)
	{
		iv.y = -1;
		while (++iv.y < size.y)
		{
			tex_x = (int)(iv.x * step.x + g->tex[C].w / 2 * degree / 180);
			tex_x %= g->tex[C].w;
			if (tex_x < 0)
				tex_x += g->tex[C].w;
			g_color = g->tex[C].data[
				(int)(step.y * iv.y) * g->tex[C].line + tex_x];
			put_pixel(&g->v, iv.x, iv.y);
		}
	}
}
