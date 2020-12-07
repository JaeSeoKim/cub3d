/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:47:42 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/07 15:21:47 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#include "cub3d_type.h"
#include "cub3d_key.h"

# define IMG_WIDTH 800
# define IMG_HEIGHT 400

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
	t_view	view;
	t_img	img;
	int		count_w;
	int		count_h;

	if (!(view.mlx_ptr = mlx_init()))
		return (1);
	if (!(view.win_ptr = mlx_new_window(view.mlx_ptr, IMG_WIDTH, IMG_HEIGHT, CUB3D_TITLE)))
		return (1);
	img.img_ptr = mlx_new_image(view.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	count_h = -1;
	while (++count_h < IMG_HEIGHT)
	{
		count_w = -1;
		while (++count_w < IMG_WIDTH)
		{
			if (count_h % 10 == 0 || count_w % 10 == 0)
				img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF;
			else
				img.data[count_h * IMG_WIDTH + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(view.mlx_ptr, view.win_ptr, img.img_ptr, 0, 0);

	mlx_hook(view.win_ptr, X_KEY_PRESS, X_KEY_PRESS_MASK, &handle_key_pressd, NULL);
	mlx_loop(view.mlx_ptr);
	return (0);
}
