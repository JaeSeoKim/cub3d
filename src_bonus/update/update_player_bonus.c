/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:35:34 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/17 15:44:55 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_player_pos(t_cub3d *g, float x, float y)
{
	t_vec	pos;

	if ('1' == g->map.data[(int)y][(int)x])
		return (0);
	if ('2' == g->map.data[(int)y][(int)x])
	{
		pos = new_vec(x - floor(x), y - floor(y));
		if ((0.2 < pos.x && pos.x < 0.8) && (0.2 < pos.y && pos.y < 0.8))
			return (0);
	}
	return (1);
}

void		update_player(t_cub3d *g)
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
	g->dir = rot_vec(g->dir, turn_dir * 60 / g->fps * TURN_S * M_PI_180);
	g->plane = rot_vec(g->plane, turn_dir * 60 / g->fps * TURN_S * M_PI_180);
	turn_vec = rot_vec(g->dir, 90 * M_PI_180);
	if (walk_dir.x != 0 || walk_dir.y != 0)
	{
		new_pos.x = g->pos.x + g->dir.x * (walk_dir.y * 60 / g->fps * WALK_S);
		new_pos.y = g->pos.y + g->dir.y * (walk_dir.y * 60 / g->fps * WALK_S);
		new_pos.x += turn_vec.x * (walk_dir.x * 60 / g->fps * WALK_S);
		new_pos.y += turn_vec.y * (walk_dir.x * 60 / g->fps * WALK_S);
		if (check_player_pos(g, new_pos.x, g->pos.y))
			g->pos.x = new_pos.x;
		if (check_player_pos(g, g->pos.x, new_pos.y))
			g->pos.y = new_pos.y;
	}
}
