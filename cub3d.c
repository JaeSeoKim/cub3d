/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:47:42 by jaeskim           #+#    #+#             */
/*   Updated: 2020/12/06 23:57:24 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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
		return (EXIT_FAILURE);
	if (!(view.win_ptr = mlx_new_window(view.mlx_ptr, 800, 400, CUBE3D_TITLE)))
		return (EXIT_FAILURE);
	mlx_key_hook(view.win_ptr, &handle_key_pressd, NULL);
	mlx_loop(view.mlx_ptr);
	return (EXIT_SUCCESS);
}
