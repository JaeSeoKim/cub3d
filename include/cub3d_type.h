/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:43:26 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/08 20:56:39 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPE_H
# define CUB3D_TYPE_H

# include "libft.h"

# define CUB3D_TITLE "jaeskim's cu3D"

typedef struct	s_ivec
{
	int			x;
	int			y;
}				t_ivec;

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
	int			walk_direct;
	int			turn_direct;
	float		angle;
	float		move_speed;
	float		rotate_speed;
}				t_player;

typedef struct	s_ray
{
	float		angle;
	float		distance;
	t_vec		wallhit;
	char		up;
	char		down;
	char		left;
	char		right;

	t_vec		intercept;
	t_vec		step;
	t_vec		vertwallhit;
	int			verthit;
	float		vertDistance;
	t_vec		horzwallhit;
	int			horzhit;
	float		horzDistance;
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
	t_ray		*rays;
	int			wall_strip_width;
	int			num_rays;
	float		fov_angle;
}				t_cub3d;

#endif
