/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:25:20 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/24 22:28:09 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_INIT_BONUS_H
# define CUB3D_INIT_BONUS_H

# include "cub3d_bonus.h"

extern	t_us g_parse_check;

void	init(t_cub3d *g, char *path, int flag);
void	init_parse(t_cub3d *g, char *path);
void	init_resolution(t_cub3d *g, char **split);
void	init_texture(t_cub3d *g, char *path, int tex_i);
void	init_map(t_cub3d *g, int fd, char *line, int *check);
void	init_player(t_cub3d *g, t_vec pos, int *flag);
void	init_sprite(t_cub3d *g);

#endif
