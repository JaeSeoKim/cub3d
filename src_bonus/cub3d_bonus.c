/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:50:30 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 03:07:01 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		main(int ac, char **av)
{
	int			flag;
	t_cub3d		g;

	flag = !ft_strcmp(av[1], "--save");
	ft_memset(&g, 0, sizeof(t_cub3d));
	if (ac < 2)
		exit_cub3d_msg(&g, "require map file");
	init(&g, av[1 + flag], flag);
	if (flag)
		return (save_bmp(&g));
	mlx_hook(g.win, X_KEY_PRESS, X_KEY_PRESS_MASK, handle_key_pressed, &g);
	mlx_hook(g.win, X_KEY_RELEASE, \
		X_KEY_RELEASE_MASK, handle_key_released, &g);
	mlx_hook(g.win, X_DESTROY_NOTIFY,
			X_SUB_STRUCTURE_NOTIFY_MASK, handle_exit_window, &g);
	mlx_loop_hook(g.mlx, handle_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
