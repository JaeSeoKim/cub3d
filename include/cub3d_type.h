/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:43:26 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/18 16:00:11 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPE_H
# define CUB3D_TYPE_H

# include "libft.h"

typedef union	u_color
{
	struct
	{
		int		b	:8;
		int		g	:8;
		int		r	:8;
		int		t	:8;
	}			bit;
	int			i;
}				t_color;

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

typedef struct	s_key
{
	char		w;
	char		a;
	char		s;
	char		d;
	char		up;
	char		down;
	char		left;
	char		right;
	char		esc;
}				t_key;

typedef struct	s_img
{
	void		*ptr;
	t_color		*data;
	int			width;
	int			height;
	int			size_l;
	int			line;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_player
{
	t_vec		pos;
	int			walk_d;
	int			turn_d;
	float		angle;
	float		move_s;
	float		rotate_s;
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
	char		was_vertical;

	t_vec		intercept;
	t_vec		step;

	char		verthit;
	t_vec		vertwallhit;
	float		vert_d;

	char		horzhit;
	t_vec		horzwallhit;
	float		horz_d;
}				t_ray;

typedef	struct	s_map
{
	int			*data;
	int			x;
	int			y;
}				t_map;

typedef struct	s_cub3d
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		*texture;
	t_key		key;
	t_player	p;
	t_map		map;
	t_ray		*rays;
	int			num_rays;
	float		fov_angle;
}				t_cub3d;

#endif
