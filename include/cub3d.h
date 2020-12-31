/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 23:19:39 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/01 00:29:00 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "cub3d_type.h"
# include "x_evnet.h"

# ifdef __APPLE__
#  include "key_mac.h"
# else
#  include "key_linux.h"
# endif

# define WALL_STRIP_WIDTH 1;

void	fill(int color);
void	stroke(int color);
void	line(t_img *view, t_vec a, t_vec b);

#endif
