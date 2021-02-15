/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_update.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:09:03 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/15 22:57:04 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UPDATE_H
# define CUB3D_UPDATE_H

# include "cub3d.h"

void	update(t_cub3d *g);
void	update_player(t_cub3d *g);
void	update_all_rays(t_cub3d *g);
void	update_sprite(t_cub3d *g);

#endif
