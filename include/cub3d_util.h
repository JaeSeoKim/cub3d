/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:32:35 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/29 21:18:40 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UTIL_H
# define CUB3D_UTIL_H

# include "cub3d.h"

t_vec	new_vec(float x, float y);
t_ivec	new_ivec(int x, int y);
t_vec	rot_vec(t_vec v, float angle);

#endif
