/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:47:42 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/07 02:20:21 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#include "cub3d_type.h"
#include "cub3d_key.h"

int		handle_key_pressd(int keycode, void *param)
{
	if (param == NULL)
	{
		if (keycode == KEY_W)
			printf("W\n");
		else if (keycode == KEY_A)
			printf("A\n");
		else if (keycode == KEY_S)
			printf("S\n");
		else if (keycode == KEY_D)
			printf("D\n");
		else if (keycode == KEY_ESC)
			printf("ESC\n");
		else if (keycode == KEY_UP)
			printf("UP\n");
		else if (keycode == KEY_DOWN)
			printf("DOWN\n");
		else if (keycode == KEY_LEFT)
			printf("LEFT\n");
		else if (keycode == KEY_RIGHT)
			printf("RIGHT\n");
	}
	return (0);
}

int		main(void)
{
	t_mlx	view;

	if (!(view.mlx_ptr = mlx_init()))
		return (1);
	if (!(view.win_ptr = mlx_new_window(view.mlx_ptr, 800, 400, CUB3D_TITLE)))
		return (1);
	mlx_hook(view.win_ptr, X_KEY_PRESS, X_KEY_PRESS_MASK, &handle_key_pressd, NULL);
	mlx_loop(view.mlx_ptr);
	return (0);
}
