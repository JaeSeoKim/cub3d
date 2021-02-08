/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:25:17 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/08 18:24:02 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define mapWidth 24
# define mapHeight 24

char	worldMap[mapWidth * mapHeight] = {
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7,
	4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1,
	4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8,
	4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1,
	4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8,
	4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1,
	4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2,
	4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2,
	4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2,
	4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};

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

static void	init_player(t_cub3d *g, t_vec pos)
{
	g->fov = FOV * M_PI_180;
	g->fov_h = g->v.width / 2 / tan(g->fov / 2);
	g->pos = pos;
	g->dir = new_vec(1, 0);
	g->plane = rot_vec(g->dir, 90 * M_PI_180);
	g->plane.x *= tan(g->fov / 2);
	g->plane.y *= tan(g->fov / 2);
}

static void	init_sprite(t_cub3d *g)
{
	int		i;

	// TODO: Map Parsing 하여 Sprite 정보 추가 필요.
	g->num_sp = 10;
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
	init_player(g, new_vec(1.5, 1.5));
	g->num_rays = g->v.width / WALL_STRIP_WIDTH;
	if (!(g->rays = malloc(sizeof(t_ray) * g->num_rays)))
		exit_cub3d(g, ERROR);
	g->map.width = mapWidth;
	g->map.height = mapHeight;
	g->map.data = (char *)worldMap;
	init_sprite(g);
}
