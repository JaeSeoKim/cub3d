/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_next_level_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 03:23:58 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 04:41:16 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	render_msg(t_cub3d *g)
{
	t_vec	position;
	t_img	*img;

	update(g);
	render(g);
	img = &g->assets[MSG_LEVELUP];
	position.x = g->v.w / 2 / 2;
	position.y = g->v.h / 2 - (g->v.w / 2 * img->h / img->w) / 2;
	put_img(g, g->v.w / 2, position, img);
	mlx_put_image_to_window(g->mlx, g->win, g->v.ptr, 0, 0);
	mlx_do_sync(g->mlx);
}

void		init_next_level(t_cub3d *g, char *path)
{
	t_ivec	screen;

	g->loading = 1;
	ft_memset(&g->poke, 0, sizeof(t_img *) * 4);
	free_data(g);
	screen = new_ivec(g->v.w, g->v.h);
	g_parse_check = 0;
	init_parse(g, path);
	g->v.w = screen.x;
	g->v.h = screen.y;
	free(path);
	g->num_rays = g->v.w / WALL_STRIP_WIDTH;
	if (!(g->rays = malloc(sizeof(t_ray) * g->num_rays)))
		exit_cub3d_msg(g, "malloc failed");
	g->life = 100;
	g->fps = 60.0;
	g->prev = clock();
	render_msg(g);
	play_sound(LEVELUP);
	play_sound(BGM);
	g->loading = 0;
}
