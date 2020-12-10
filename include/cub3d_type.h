/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:43:26 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/07 02:01:41 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPE_H
# define CUB3D_TYPE_H

# include "libft.h"

# define CUB3D_TITLE	"jaeskim's cu3D"

typedef struct	s_view
{
	void		*mlx;
	void		*win;
}				t_view;

typedef struct	s_img
{
	void		*ptr;
	t_ui		*data;
	int			width;
	int			height;

	int			size_l;
	int			arr_l;
	int			bpp;
	int			endian;
}				t_img;

#endif
