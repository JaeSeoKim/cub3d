/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:43:26 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/31 23:07:58 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPE_H
# define CUB3D_TYPE_H

# include "libft.h"

# define CUB3D_TITLE "jaeskim's cu3D"

typedef struct	s_vec
{
	float		x;
	float		y;
}				t_vec;

typedef struct	s_img
{
	void		*ptr;
	t_ui		*data;
	int			size_l;
	int			line;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_player
{
	t_vec		vec;
	int			walkDirection;
	int			turnDirection;
	float		rotationAngle;
	float		moveSpeed;
	float		rotateSpeed;
}				t_player;

typedef struct	s_ray
{
	float		rayAngle;
	float		wallHitX;
	float		wallHitY;
	float		distance;
}				t_ray;

typedef struct	s_cub3d
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_ll		key[6];
	t_img		img;
	t_player	player;
	t_ray		rays[1];
}				t_cub3d;

#endif
