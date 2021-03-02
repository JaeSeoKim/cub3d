/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:25:17 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/02 22:40:47 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_window(t_cub3d *g, int flag)
{
	if (!flag)
	{
		if (!(g->win =
			mlx_new_window(g->mlx, g->v.w, g->v.h, CUB3D_TITLE)))
			exit_cub3d_msg(g, "fail mlx_new_window()");
	}
	if (!(g->v.ptr = mlx_new_image(g->mlx, g->v.w, g->v.h)))
		exit_cub3d_msg(g, "fail mlx_new_image()");
	if (!(g->v.data = (t_color *)mlx_get_data_addr(
		g->v.ptr, &g->v.bpp, &g->v.size_l, &g->v.endian)))
		exit_cub3d_msg(g, "fail mlx_get_data_addr()");
	g->v.line = g->v.size_l / (g->v.bpp / 8);
}

void		init(t_cub3d *g, char *path, int flag)
{
	(!(g->mlx = mlx_init()) ? exit_cub3d_msg(g, "fail mlx_init()") : 0);
	mlx_get_screen_size(g->mlx, &g->v.w, &g->v.h);
	init_parse(g, path);
	init_window(g, flag);
	g->num_rays = g->v.w / WALL_STRIP_WIDTH;
	if (!(g->rays = malloc(sizeof(t_ray) * g->num_rays)))
		exit_cub3d_msg(g, "malloc failed");
	g->key.m = 1;
	g->map_size = 7;
	g->shadow = g->fov_h / 30;
	g->prev = clock();
	g->fps = 60.0;
	g->life = 100;
	init_assts(g);
	(!flag ? play_sound(BGM) : 0);
}
