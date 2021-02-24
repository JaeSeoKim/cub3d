/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:25:30 by jaeskim           #+#    #+#             */
/*   Updated: 2021/02/25 00:51:02 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_us	g_parse_check = 0;

static void		switch_sprite(t_cub3d *g, char **split, int word_cnt)
{
	if (!ft_strcmp(split[0], "S_Y") && word_cnt == 2)
		init_texture(g, split[1], S_Y);
	else if (!ft_strcmp(split[0], "S_R") && word_cnt == 2)
		init_texture(g, split[1], S_R);
	else if (!ft_strcmp(split[0], "S_G") && word_cnt == 2)
		init_texture(g, split[1], S_G);
	else if (!ft_strcmp(split[0], "S_B") && word_cnt == 2)
		init_texture(g, split[1], S_B);
	else if (!ft_strcmp(split[0], "S_Y2") && word_cnt == 2)
		init_texture(g, split[1], S_Y2);
	else if (!ft_strcmp(split[0], "S_R2") && word_cnt == 2)
		init_texture(g, split[1], S_R2);
	else if (!ft_strcmp(split[0], "S_G2") && word_cnt == 2)
		init_texture(g, split[1], S_G2);
	else if (!ft_strcmp(split[0], "S_B2") && word_cnt == 2)
		init_texture(g, split[1], S_B2);
	else
		exit_cub3d_msg(g, "invaild map file");
}

static void		switch_parse(t_cub3d *g, char **split, int word_cnt)
{
	if (!ft_strcmp(split[0], "R") && word_cnt == 3)
		init_resolution(g, &split[1]);
	else if (!ft_strcmp(split[0], "NO") && word_cnt == 2)
		init_texture(g, split[1], NO);
	else if (!ft_strcmp(split[0], "SO") && word_cnt == 2)
		init_texture(g, split[1], SO);
	else if (!ft_strcmp(split[0], "EA") && word_cnt == 2)
		init_texture(g, split[1], EA);
	else if (!ft_strcmp(split[0], "WE") && word_cnt == 2)
		init_texture(g, split[1], WE);
	else if (!ft_strcmp(split[0], "F") && word_cnt == 2)
		init_texture(g, split[1], F);
	else if (!ft_strcmp(split[0], "C") && word_cnt == 2)
		init_texture(g, split[1], C);
	else
		switch_sprite(g, split, word_cnt);
}

static void		check_parse_type(t_cub3d *g, char *line)
{
	int		word_cnt;
	char	**split;

	if (ft_strlen(line))
	{
		if (!(split = ft_split_cnt(line, ' ', &word_cnt)))
			exit_cub3d_msg(g, "malloc failed");
		switch_parse(g, split, word_cnt);
		ft_free_split(split, word_cnt);
	}
	free(line);
}

static int		extention_check(char *path)
{
	int		len;

	if ((len = ft_strlen(path)) < 4)
		return (ERROR);
	if (path[len - 1] == 'b' && path[len - 2] == 'u' \
		&& path[len - 3] == 'c' && path[len - 4] == '.')
		return (SUCCES);
	return (ERROR);
}

void			init_parse(t_cub3d *g, char *path)
{
	int		fd;
	int		check;
	char	*line;

	if (extention_check(path))
		exit_cub3d_msg(g, "invaild file extension. (.cub)");
	if ((fd = open(path, O_RDONLY)) == -1)
		exit_cub3d_msg(g, "file open fail...");
	while ((g_parse_check != (1 << (R + 1)) - 1) && \
			(check = get_next_line(fd, &line)) >= 0)
		check_parse_type(g, line);
	if (check < 0)
		exit_cub3d_msg(g, !check ? "invaild map file" : "file read error");
	while ((check = get_next_line(fd, &line)) > 0 && !ft_strlen(line))
		free(line);
	init_map(g, fd, line, &check);
	init_sprite(g);
	close(fd);
}
