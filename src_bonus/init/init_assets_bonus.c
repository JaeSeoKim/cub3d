/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:35:13 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 03:52:21 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	load_asset(t_cub3d *g, char *path, int tex_i)
{
	t_img	*img;

	img = &g->assets[tex_i];
	if (!(img->ptr = \
		mlx_xpm_file_to_image(g->mlx, path, &img->w, &img->h)))
		exit_cub3d_msg(g, ft_strjoin("assets load fail need ", path));
	if (!(img->data = (t_color *)mlx_get_data_addr(\
			img->ptr, &img->bpp, &img->size_l, &img->endian)))
		exit_cub3d_msg(g, "texture data addr load fail..");
	img->line = img->size_l / (img->bpp / 8);
}

void		init_assts(t_cub3d *g)
{
	load_asset(g, LIFEBAR_PATH, LIFEBAR);
	load_asset(g, MSG_GAMEOVER_PATH, MSG_GAMEOVER);
	load_asset(g, MSG_GAMEWIN_PATH, MSG_GAMEWIN);
	load_asset(g, MSG_LEVELUP_PATH, MSG_LEVELUP);
}
