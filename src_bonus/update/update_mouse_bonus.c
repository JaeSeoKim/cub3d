/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 22:52:56 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/22 23:46:05 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_mouse(t_cub3d *g)
{
	if (g->key.p)
	{
		mlx_mouse_get_pos(g->win, &g->mouse.x, &g->mouse.y);
		mlx_mouse_move(g->win, g->v.w / 2, g->v.h / 2);
	}
}
