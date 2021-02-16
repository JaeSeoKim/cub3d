/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_type_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:39:01 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 18:42:14 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPE_BONUS_H
# define CUB3D_TYPE_BONUS_H

# include "cub3d_bonus.h"

typedef struct	s_vec
{
	float		x;
	float		y;
}				t_vec;

typedef struct	s_ivec
{
	int			x;
	int			y;
}				t_ivec;

typedef union	u_color
{
	struct
	{
		t_ui	b	:8;
		t_ui	g	:8;
		t_ui	r	:8;
		t_ui	t	:8;
	}			bit;
	int			i;
}				t_color;

typedef struct	s_key
{
	char		w		:1;
	char		a		:1;
	char		s		:1;
	char		d		:1;
	char		up		:1;
	char		down	:1;
	char		left	:1;
	char		right	:1;
	char		esc		:1;
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

typedef struct	s_ray
{
	t_vec		dir;
	t_ivec		map;
	float		dist;
	char		side;
	t_img		*tex;
}				t_ray;

typedef struct	s_map
{
	char		**data;
	int			w;
	int			h;
}				t_map;

typedef struct	s_sprite
{
	t_vec		pos;
	t_vec		trans;
	t_img		*tex;
}				t_sprite;

typedef struct	s_cub3d
{
	void		*mlx;
	void		*win;
	t_img		v;

	t_key		key;

	t_img		tex[7];

	int			num_rays;
	t_ray		*rays;

	int			num_sp;
	t_sprite	*sp;
	int			*sp_order;
	float		*sp_dist;

	t_map		map;

	t_color		bg_color[2];

	float		fov;
	float		fov_h;
	t_vec		dir_plane;
	t_vec		dir;
	t_vec		plane;
	t_vec		pos;
}				t_cub3d;

#endif
