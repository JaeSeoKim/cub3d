/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:21:25 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/26 17:25:27 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

float	normal_angle(float angle)
{
	if ((angle = fmodf(angle, M_2PI)) < 0)
		angle += M_2PI;
	return (angle);
}
