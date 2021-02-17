/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:21:25 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/17 22:20:59 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vec	new_vec(float x, float y)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_ivec	new_ivec(int x, int y)
{
	t_ivec	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vec	rot_vec(t_vec v, float angle)
{
	t_vec result;
	t_vec rotate;

	if (angle == 0)
		return (v);
	rotate = new_vec(cos(angle), sin(angle));
	result.x = rotate.x * v.x - rotate.y * v.y;
	result.y = rotate.y * v.x + rotate.x * v.y;
	return (result);
}

t_vec	nor_pos(t_cub3d *g, t_vec pos)
{
	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > g->v.w)
		pos.x = g->v.w - 1;
	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y > g->v.h)
		pos.y = g->v.h - 1;
	return (pos);
}

t_ivec	nor_int_size(t_ivec size, t_ivec pos)
{
	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > size.x)
		pos.x = size.x - 1;
	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y > size.y)
		pos.y = size.y - 1;
	return (pos);
}
