/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:47:42 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/07 01:09:30 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <X11/X.h>
#include "libft.h"
#include "cube3d_type.h"

int		handle_key_pressd(int keycode, void *param)
{
	if (param == NULL)
		printf("keycode : %d\n", keycode);
	return (0);
}

int		main(void)
{
	t_mlx	view;

	if (!(view.mlx_ptr = mlx_init()))
		return (1);
	if (!(view.win_ptr = mlx_new_window(view.mlx_ptr, 800, 400, CUBE3D_TITLE)))
		return (1);
	mlx_hook(view.win_ptr, KeyPress, KeyPressMask, &handle_key_pressd, NULL);
	mlx_loop(view.mlx_ptr);
	return (0);
}
