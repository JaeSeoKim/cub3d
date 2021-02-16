/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:35:34 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 21:16:03 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player(t_cub3d *g)
{
	int		turn_dir;
	t_ivec	walk_dir;
	t_vec	turn_vec;
	t_vec	new_pos;

	turn_dir = g->key.left ? -1 : 0;
	turn_dir += g->key.right ? 1 : 0;
	walk_dir.y = g->key.w ? 1 : 0;
	walk_dir.y += g->key.s ? -1 : 0;
	walk_dir.x = g->key.a ? -1 : 0;
	walk_dir.x += g->key.d ? 1 : 0;
	g->dir = rot_vec(g->dir, turn_dir * (60 / g->fps) * TURN_S * M_PI_180);
	g->plane = rot_vec(g->plane, turn_dir * (60 / g->fps) * TURN_S * M_PI_180);
	turn_vec = rot_vec(g->dir, 90 * M_PI_180);
	if (walk_dir.x != 0 || walk_dir.y != 0)
	{
		new_pos.x = g->pos.x + g->dir.x * (walk_dir.y * (60 / g->fps) * WALK_S);
		new_pos.y = g->pos.y + g->dir.y * (walk_dir.y * (60 / g->fps) * WALK_S);
		new_pos.x += turn_vec.x * (walk_dir.x * (60 / g->fps) * WALK_S);
		new_pos.y += turn_vec.y * (walk_dir.x * (60 / g->fps) * WALK_S);
		if (g->map.data[(int)g->pos.y][(int)new_pos.x] != '1')
			g->pos.x = new_pos.x;
		if (g->map.data[(int)new_pos.y][(int)g->pos.x] != '1')
			g->pos.y = new_pos.y;
	}
}
