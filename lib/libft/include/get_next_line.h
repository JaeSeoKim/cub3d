/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 17:49:05 by jaeskim           #+#    #+#             */
/*   Updated: 2020/11/24 22:18:02 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/*
** windows, linux doesn't have OPEN_MAX Constants
** OPEN_MAX value from Mac Os
*/

# ifndef OPEN_MAX
#  define OPEN_MAX	10240
# endif

int		get_next_line(int fd, char **line);

#endif
