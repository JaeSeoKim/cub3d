/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:28:36 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/15 22:57:07 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_cub3d(t_cub3d *g, int code)
{
	exit(g ? code : 0);
}

void	exit_cub3d_msg(t_cub3d *g, char *msg)
{
	write(STDERR_FILENO, "ERROR\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit_cub3d(g, ERROR);
}
