/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:25:17 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/28 23:04:56 by jaeskim          ###   ########.fr       */
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

int		load_texture(t_cub3d *g, t_img *img, char *path)
{
	if (!(img->ptr = \
		mlx_xpm_file_to_image(g->mlx, path, &img->width, &img->height)))
		return (ERROR);
	img->data = (t_color *)mlx_get_data_addr(\
		img->ptr, &img->bpp, &img->size_l, &img->endian);
	img->line = img->size_l / (img->bpp / 8);
	return (SUCCES);
}

static void	init_window(t_cub3d *g, int width, int height, char *title)
{
	if (!(g->mlx = mlx_init()))
		exit(ERROR);
	if (!(g->win = mlx_new_window(g->mlx, width, height, title)))
		exit_cub3d(g, ERROR);
	g->v.width = width;
	g->v.height = height;
	if (!(g->v.ptr = mlx_new_image(g->mlx, width, height)))
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

static void	init_texture(t_cub3d *g)
{
	(load_texture(g, &g->tex[0], "./img/wall_n.xpm") ? exit_cub3d(g, ERROR) : 0);
	(load_texture(g, &g->tex[1], "./img/wall_s.xpm") ? exit_cub3d(g, ERROR) : 0);
	(load_texture(g, &g->tex[2], "./img/wall_e.xpm") ? exit_cub3d(g, ERROR) : 0);
	(load_texture(g, &g->tex[3], "./img/wall_w.xpm") ? exit_cub3d(g, ERROR) : 0);

	// TODO: FLOOR, CELING, SPRITE Texture 추가 필요!
	// (!load_texture(g, &g->tex[4], "./img/") ? exit_cub3d(g, ERROR) : 0);
	// (!load_texture(g, &g->tex[5], "./img/") ? exit_cub3d(g, ERROR) : 0);
	// (!load_texture(g, &g->tex[6], "./img/") ? exit_cub3d(g, ERROR) : 0);
	// (!load_texture(g, &g->tex[7], "./img/") ? exit_cub3d(g, ERROR) : 0);
}

void		init(t_cub3d *g, int width, int height, char *title)
{
	ft_memset(g, 0, sizeof(t_cub3d));
	init_window(g, width, height, title);
	init_player(g, new_vec(1.5, 1.5));
	g->num_rays = g->v.width / WALL_STRIP_WIDTH;
	if (!(g->rays = malloc(sizeof(t_ray) * g->num_rays)))
		exit_cub3d(g, ERROR);
	g->map.width = mapWidth;
	g->map.height = mapHeight;
	g->map.data = (char *)worldMap;
	g->ceiling = rgba(75, 173, 220, 1);
	g->floor = rgba(167, 217, 107, 1);
	init_texture(g);
}
