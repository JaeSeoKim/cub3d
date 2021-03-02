/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_finish_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 03:02:12 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 04:45:39 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_finish(t_cub3d *g)
{
	t_vec	position;
	t_img	*img;

	system("kill `pgrep -f afplay` 2> /dev/null");
	printf("You Win...!");
	img = &g->assets[MSG_GAMEWIN];
	position.x = g->v.w / 2 / 2;
	position.y = g->v.h / 2 - (g->v.w / 2 * img->h / img->w) / 2;
	put_img(g, g->v.w / 2, position, img);
	mlx_put_image_to_window(g->mlx, g->win, g->v.ptr, 0, 0);
	mlx_do_sync(g->mlx);
	play_sound(GAMEWIN);
	exit_cub3d(g, SUCCES);
}
