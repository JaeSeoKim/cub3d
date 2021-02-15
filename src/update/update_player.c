/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:35:34 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/15 22:37:35 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(t_cub3d *g)
{
	int		walk_dir;
	int		turn_dir;
	t_vec	new_pos;

	turn_dir = g->key.a ? -1 : 0;
	turn_dir += g->key.d ? 1 : 0;
	walk_dir = g->key.w ? 1 : 0;
	walk_dir += g->key.s ? -1 : 0;
	g->dir = rot_vec(g->dir, turn_dir * TURN_S * M_PI_180);
	g->plane = rot_vec(g->plane, turn_dir * TURN_S * M_PI_180);
	if (walk_dir != 0)
	{
		new_pos.x = g->pos.x + g->dir.x * (walk_dir * WALK_S);
		new_pos.y = g->pos.y + g->dir.y * (walk_dir * WALK_S);
		if (g->map.data[(int)g->pos.y][(int)new_pos.x] != '1')
			g->pos.x = new_pos.x;
		if (g->map.data[(int)new_pos.y][(int)g->pos.x] != '1')
			g->pos.y = new_pos.y;
	}
}
