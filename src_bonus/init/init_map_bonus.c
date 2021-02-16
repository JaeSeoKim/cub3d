/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:53:47 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/16 17:14:19 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_map_setup(t_cub3d *g, int size, int max, t_list *lst)
{
	t_list	*curr;
	int		i;

	curr = lst;
	if (!(g->map.data = malloc(sizeof(char **) * size)))
		exit_cub3d_msg(g, "malloc failed");
	g->map.w = max;
	g->map.h = size;
	i = -1;
	while (++i < size)
	{
		if (!(g->map.data[i] = malloc(max + 1)))
			exit_cub3d_msg(g, "malloc failed");
		ft_memset(g->map.data[i], ' ', max);
		ft_memmove(g->map.data[i], curr->content, ft_strlen(curr->content));
		g->map.data[i][max] = 0;
		curr = curr->next;
	}
	ft_lstclear(&lst, free);
}

static void	init_map_parsing(t_cub3d *g, int fd, char *line, int *check)
{
	int		max;
	t_list	*curr;
	t_list	*tmp;

	if (!(curr = ft_lstnew(line)))
		exit_cub3d_msg(g, "malloc failed");
	max = ft_strlen(line);
	while ((*check = get_next_line(fd, &line)) >= 0 && ft_strlen(line))
	{
		if (!(tmp = ft_lstnew(line)))
			exit_cub3d_msg(g, "malloc failed");
		ft_lstadd_back(&curr, tmp);
		max = max > (int)ft_strlen(line) ? max : ft_strlen(line);
	}
	if (*check == -1)
		exit_cub3d_msg(g, "file read error");
	free(line);
	init_map_setup(g, ft_lstsize(curr), max, curr);
}

static void	check_map(t_cub3d *g, t_ivec p)
{
	t_map	*m;

	m = &g->map;
	if (!ft_strchr(" 012NSWE", m->data[p.y][p.x]) ||
		((p.y == 0 || p.x == 0 || p.y == m->h - 1 || p.x == m->w - 1) &&
		!ft_strchr(" 1", m->data[p.y][p.x])))
		exit_cub3d_msg(g, "invaild map file");
	if (m->data[p.y][p.x] == ' ')
	{
		if ((p.y != 0 && !ft_strchr(" 1", m->data[p.y - 1][p.x])) ||
			(p.x != 0 && !ft_strchr(" 1", m->data[p.y][p.x - 1])) ||
			(p.y < m->h - 1 && !ft_strchr(" 1", m->data[p.y + 1][p.x])) ||
			(p.x < m->w - 1 && !ft_strchr(" 1", m->data[p.y][p.x + 1])))
			exit_cub3d_msg(g, "invaild map file");
	}
}

void		init_map(t_cub3d *g, int fd, char *line, int *check)
{
	int		i;
	int		flag;

	init_map_parsing(g, fd, line, check);
	flag = 0;
	i = -1;
	while (++i < g->map.w * g->map.h)
	{
		check_map(g, new_ivec(i % g->map.w, i / g->map.w));
		if (ft_strchr("NSWE", g->map.data[i / g->map.w][i % g->map.w]))
			init_player(g, new_vec(i % g->map.w, i / g->map.w), &flag);
	}
	if (!flag)
		exit_cub3d_msg(g, "parsing player postion error");
}
