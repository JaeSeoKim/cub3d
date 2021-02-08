/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:25:17 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/08 22:20:21 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_window(t_cub3d *g)
{
	if (!(g->win =
		mlx_new_window(g->mlx, g->v.width, g->v.height, CUB3D_TITLE)))
		exit_cub3d(g, ERROR);
	if (!(g->v.ptr = mlx_new_image(g->mlx, g->v.width, g->v.height)))
		exit_cub3d(g, ERROR);
	g->v.data = (t_color *)mlx_get_data_addr(
		g->v.ptr, &g->v.bpp, &g->v.size_l, &g->v.endian);
	g->v.line = g->v.size_l / (g->v.bpp / 8);
}

static void	init_player(t_cub3d *g)
{
	g->fov = FOV * M_PI_180;
	g->fov_h = g->v.width / 2 / tan(g->fov / 2);
	g->plane = rot_vec(g->dir, 90 * M_PI_180);
	g->plane.x *= tan(g->fov / 2);
	g->plane.y *= tan(g->fov / 2);
}

static void	init_sprite(t_cub3d *g)
{
	int		i;

	// TODO: Map Parsing 하여 Sprite 정보 추가 필요.
	g->num_sp = 0;
	g->sp = malloc(sizeof(t_sprite) * g->num_sp);
	g->sp_order = malloc(sizeof(int) * g->num_sp);
	g->sp_dist = malloc(sizeof(float) * g->num_sp);
	i = -1;
	while (++i < g->num_sp)
	{
		g->sp[i].pos = new_vec(6.5 + i, 2.5 + i);
		g->sp[i].tex = &g->tex[S];
	}
}

void		init(t_cub3d *g, char *path)
{
	ft_memset(g, 0, sizeof(t_cub3d));
	(!(g->mlx = mlx_init()) ? exit_cub3d_msg(g, "fail mlx_init()") : 0);
	mlx_get_screen_size(g->mlx, &g->v.width, &g->v.height);
	init_parse(g, path);
	init_window(g);
	init_player(g);
	g->num_rays = g->v.width / WALL_STRIP_WIDTH;
	if (!(g->rays = malloc(sizeof(t_ray) * g->num_rays)))
		exit_cub3d(g, ERROR);
	init_sprite(g);
}
