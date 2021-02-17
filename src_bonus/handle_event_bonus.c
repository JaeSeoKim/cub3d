/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:57:51 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/17 14:51:47 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		handle_key_pressed(int keycode, t_cub3d *g)
{
	(keycode == KEY_W ? g->key.w = 1 : 0);
	(keycode == KEY_A ? g->key.a = 1 : 0);
	(keycode == KEY_S ? g->key.s = 1 : 0);
	(keycode == KEY_D ? g->key.d = 1 : 0);
	(keycode == KEY_UP ? g->key.up = 1 : 0);
	(keycode == KEY_DOWN ? g->key.down = 1 : 0);
	(keycode == KEY_LEFT ? g->key.left = 1 : 0);
	(keycode == KEY_RIGHT ? g->key.right = 1 : 0);
	(keycode == KEY_M ? g->key.m = !g->key.m : 0);
	(keycode == KEY_PLUS && g->map_size > 2 ? g->map_size-- : 0);
	(keycode == KEY_MINUS && g->map_size < 7 ? g->map_size++ : 0);
	if (keycode == KEY_ESC)
		exit_cub3d(g, SUCCES);
	return (0);
}

int		handle_key_released(int keycode, t_cub3d *g)
{
	(keycode == KEY_W ? g->key.w = 0 : 0);
	(keycode == KEY_A ? g->key.a = 0 : 0);
	(keycode == KEY_S ? g->key.s = 0 : 0);
	(keycode == KEY_D ? g->key.d = 0 : 0);
	(keycode == KEY_UP ? g->key.up = 0 : 0);
	(keycode == KEY_DOWN ? g->key.down = 0 : 0);
	(keycode == KEY_LEFT ? g->key.left = 0 : 0);
	(keycode == KEY_RIGHT ? g->key.right = 0 : 0);
	return (0);
}

int		handle_exit_window(t_cub3d *g)
{
	exit_cub3d(g, SUCCES);
	return (0);
}

int		handle_loop(t_cub3d *g)
{
	clock_t	now;

	now = clock();
	g->fps = CLOCKS_PER_SEC / (now - g->prev);
	update(g);
	render(g);
	mlx_put_image_to_window(g->mlx, g->win, g->v.ptr, 0, 0);
	mlx_do_sync(g->mlx);
	g->prev = now;
	return (0);
}
