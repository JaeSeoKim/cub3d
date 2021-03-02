/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:24:27 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/03 04:45:40 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	play_sound(int type)
{
	char	*cmd;

	cmd = 0;
	if (type == BGM)
		system((cmd = ft_strjoin_free(\
			ft_strjoin("afplay ", BGM_PATH), " &", 1)));
	else if (type == CATCH)
		system((cmd = ft_strjoin_free(\
			ft_strjoin("afplay ", CATCH_PATH), " &", 1)));
	else if (type == POTION)
		system((cmd = ft_strjoin_free(\
			ft_strjoin("afplay ", POTION_PATH), " &", 1)));
	else if (type == GAMEOVER)
		system((cmd = ft_strjoin("afplay ", GAMEOVER_PATH)));
	else if (type == GAMEWIN)
		system((cmd = ft_strjoin("afplay ", GAMEWIN_PATH)));
	else if (type == LEVELUP)
		system((cmd = ft_strjoin("afplay ", LEVELUP_PATH)));
	if (cmd)
		free(cmd);
}
