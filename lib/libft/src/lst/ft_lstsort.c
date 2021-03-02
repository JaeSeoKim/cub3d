/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:57:35 by jaeskim           #+#    #+#             */
/*   Updated: 2021/03/02 23:20:42 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **lst, int (*compare)(t_list *a, t_list *b))
{
	t_list	**bubble_a;
	t_list	**bubble_b;
	void	*tmp;

	bubble_a = lst;
	while ((*bubble_a)->next)
	{
		bubble_b = &(*bubble_a)->next;
		while ((*bubble_b))
		{
			if ((*compare)(*bubble_a, *bubble_b))
			{
				tmp = (*bubble_a)->content;
				(*bubble_a)->content = (*bubble_b)->content;
				(*bubble_b)->content = tmp;
			}
			bubble_b = &(*bubble_b)->next;
		}
		bubble_a = &(*bubble_a)->next;
	}
}
