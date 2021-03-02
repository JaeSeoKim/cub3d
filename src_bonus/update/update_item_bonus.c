/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_item_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:05:56 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 04:16:50 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	add_pokemon(t_cub3d *g, t_list *curr)
{
	int		i;

	i = -1;
	while (++i < 4 && g->poke[i])
		;
	(i < 4 ? (g->poke[i] = ((t_sprite *)curr->content)->tex) : 0);
}

static void	remove_sprite(t_cub3d *g, int flag)
{
	t_vec	pos;
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = g->sp;
	while (curr)
	{
		pos = ((t_sprite *)curr->content)->pos;
		if ((int)pos.x == (int)g->pos.x && (int)pos.y == (int)g->pos.y)
		{
			(flag ? add_pokemon(g, curr) : 0);
			if (prev)
				prev->next = curr->next;
			else
				g->sp = curr->next;
			ft_lstdelone(curr, free);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void		update_item(t_cub3d *g)
{
	if ('H' == g->map.data[(int)g->pos.y][(int)g->pos.x])
	{
		play_sound(POTION);
		g->map.data[(int)g->pos.y][(int)g->pos.x] = '0';
		remove_sprite(g, 0);
		g->life += 30;
	}
	if (ft_strchr(S_J, g->map.data[(int)g->pos.y][(int)g->pos.x]))
	{
		g->map.data[(int)g->pos.y][(int)g->pos.x] = '0';
		remove_sprite(g, 1);
		play_sound(CATCH);
	}
}
