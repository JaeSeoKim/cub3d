/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resolution_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:00:01 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/17 19:41:41 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	itoa(t_cub3d *g, char *word)
{
	int		len;
	int		n;

	n = 0;
	len = ft_strlen(word);
	while (len > 0 && ft_strchr("0123456789", *word))
	{
		n *= 10;
		n += *word++ - '0';
		--len;
	}
	if (len != 0)
		exit_cub3d_msg(g, "parsing error resolution");
	return (n);
}

void		init_resolution(t_cub3d *g, char **split)
{
	t_ivec	resolution;

	if (((g_parse_check >> R) & 1) == 1)
		exit_cub3d_msg(g, "invaild map file");
	g_parse_check |= 1 << R;
	resolution.x = itoa(g, split[0]);
	resolution.y = itoa(g, split[1]);
	if (resolution.x < g->v.w)
		g->v.w = resolution.x;
	if (resolution.y < g->v.h)
		g->v.h = resolution.y;
}
