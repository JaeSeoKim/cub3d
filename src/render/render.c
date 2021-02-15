/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:26:11 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/15 22:42:05 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		render(t_cub3d *g)
{
	render_floor(g);
	render_ceiling(g);
	render_wall(g);
	render_sprite(g);
}
