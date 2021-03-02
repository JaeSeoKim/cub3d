/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 23:46:07 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/02 23:31:32 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*check_tex(t_cub3d *g, char c)
{
	if (c == 'Y')
		return (&g->tex[S_Y]);
	else if (c == 'R')
		return (&g->tex[S_R]);
	else if (c == 'G')
		return (&g->tex[S_G]);
	else if (c == 'B')
		return (&g->tex[S_B]);
	else if (c == 'H')
		return (&g->tex[S_H]);
	else if (c == 'O')
		return (&g->tex[S_O]);
	return (0);
}

void			parsing_sprite(t_cub3d *g, t_list **lst, t_list **curr)
{
	int			i;
	t_sprite	*tmp;

	*lst = 0;
	i = -1;
	while (++i < g->map.w * g->map.h)
	{
		if (ft_strchr(S, g->map.data[i / g->map.w][i % g->map.w]))
		{
			if (!(tmp = malloc(sizeof(t_sprite))))
				exit_cub3d_msg(g, "malloc failed");
			tmp->pos = new_vec(i % g->map.w + 0.5, i / g->map.w + 0.5);
			tmp->tex = check_tex(g, g->map.data[i / g->map.w][i % g->map.w]);
			tmp->base = g->map.data[i / g->map.w][i % g->map.w];
			if (!*lst)
				(!(*lst = ft_lstnew(tmp)) ?
					exit_cub3d_msg(g, "malloc failed") : 0);
			else if (!(*curr = ft_lstnew(tmp)))
				exit_cub3d_msg(g, "malloc failed");
			else
				ft_lstadd_back(lst, *curr);
		}
	}
}

void			init_sprite(t_cub3d *g)
{
	t_list		*lst;
	t_list		*curr;

	parsing_sprite(g, &lst, &curr);
	g->sp = lst;
}
