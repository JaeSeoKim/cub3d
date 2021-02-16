/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:35:13 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 17:09:19 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_texture(t_cub3d *g, char *path, int tex_i)
{
	t_img	*img;

	if (((g_parse_check >> tex_i) & 1) == 1)
		exit_cub3d_msg(g, "invaild map file");
	g_parse_check |= 1 << tex_i;
	img = &g->tex[tex_i];
	if (!(img->ptr = \
		mlx_xpm_file_to_image(g->mlx, path, &img->width, &img->height)))
		exit_cub3d_msg(g, "texture load fail");
	if (!(img->data = (t_color *)mlx_get_data_addr(\
			img->ptr, &img->bpp, &img->size_l, &img->endian)))
		exit_cub3d_msg(g, "texture data addr load fail..");
	img->line = img->size_l / (img->bpp / 8);
}
