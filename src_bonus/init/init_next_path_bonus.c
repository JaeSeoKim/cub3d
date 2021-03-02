/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_next_path_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 03:15:34 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 04:16:48 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_next_path(t_cub3d *g, char *path)
{
	if (((g_parse_check >> NEXT) & 1) == 1)
		exit_cub3d_msg(g, "invaild map file");
	g_parse_check |= 1 << NEXT;
	if (!ft_strcmp(path, "FINISH"))
		g->next_level = 0;
	else
		g->next_level = ft_strdup(path);
}
