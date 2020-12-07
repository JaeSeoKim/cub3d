/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:47:42 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/07 20:50:25 by jaeskim          ###   ########.fr       */
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
	t_view view;
	t_img img;
	int count_w;
	int count_h;

	if (!(view.mlx = mlx_init()))
		return (1);
	if (!(view.win = mlx_new_window(view.mlx, 800, 400, CUB3D_TITLE)))
		return (1);
	img.ptr = mlx_new_image(view.mlx, 800, 400);
	img.data = (t_ui *)mlx_get_data_addr(\
		img.ptr, &img.bpp, &img.size_l, &img.endian);
	img.arr_l = img.size_l / (img.bpp / 8);
	count_h = -1;
	while (++count_h < 400)
	{
		count_w = -1;
		while (++count_w < 800)
		{
			if (count_h % 100 == 0 || count_w % 100 == 0)
				img.data[img.arr_l * count_h + count_w] = 0xFFFFFF;
			else
				img.data[img.arr_l * count_h + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(view.mlx, view.win, img.ptr, 0, 0);
	mlx_hook(view.win, X_KEY_PRESS, X_KEY_PRESS_MASK, &handle_key_pressd, NULL);
	mlx_loop(view.mlx);
	return (0);
}
