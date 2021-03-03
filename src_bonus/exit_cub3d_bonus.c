/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:28:36 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/04 01:49:25 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_free(void *memory)
{
	if (memory)
		free(memory);
}

void		free_data(t_cub3d *g)
{
	int		i;

	i = -1;
	while (++i < TEX_SIZE)
		(g->tex[i].ptr ? mlx_destroy_image(g->mlx, g->tex[i].ptr) : 0);
	ft_memset(g->tex, 0, sizeof(t_img) * TEX_SIZE);
	check_free(g->rays);
	g->rays = 0;
	ft_lstclear(&g->sp, check_free);
	if (g->map.data)
	{
		i = -1;
		while (++i < g->map.h)
			check_free(g->map.data[i]);
		free(g->map.data);
	}
	g->map.data = 0;
}

void		exit_cub3d(t_cub3d *g, int code)
{
	int		i;

	free_data(g);
	i = -1;
	while (++i < ASSETS_SIZE)
		(g->assets[i].ptr ? mlx_destroy_image(g->mlx, g->assets[i].ptr) : 0);
	(g->v.ptr ? mlx_destroy_image(g->mlx, g->v.ptr) : 0);
	(g->win ? mlx_destroy_window(g->mlx, g->win) : 0);
	(g->mlx ? mlx_destroy_display(g->mlx) : 0);
	system("kill `pgrep -f afplay` 2> /dev/null");
	exit(g ? code : 0);
}

void		exit_cub3d_msg(t_cub3d *g, char *msg)
{
	write(STDERR_FILENO, "ERROR\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit_cub3d(g, ERROR);
}
