/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_count_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:49:54 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 03:22:51 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_count(t_cub3d *g)
{
	g->count.min += 60 / g->fps / 60;
	g->count.sec += 60 / g->fps;
	if (g->count.min > 60)
		g->count.min = 0;
	if (g->count.sec > 60)
	{
		g->count.sec = 0;
		g->life -= 1;
	}
}
