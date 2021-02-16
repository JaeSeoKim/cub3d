/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:38:28 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 17:25:46 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_floor(t_cub3d *g)
{
	g_color = g->bg_color[F - F];
	rect(&g->v, new_vec(0, g->v.height / 2), g->v.width, g->v.height / 2);
}
