/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 23:19:39 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/09 21:08:04 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "cub3d_type.h"
# include "x_evnet.h"

# include "minilibx_util.h"

# ifdef __APPLE__
#  include "key_mac.h"
# else
#  include "key_linux.h"
# endif

# define M_PI	3.14159265358979323846264338327950288
# define M_PI_2	1.57079632679489661923132169163975144
# define M_PI_4	0.785398163397448309615660845819875721
# define WALL_STRIP_WIDTH 1;

#endif
