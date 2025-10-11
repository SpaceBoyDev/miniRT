/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 20:05:14 by dario             #+#    #+#             */
/*   Updated: 2025/03/28 20:32:44 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *newlst)
{
	t_lst	*node;

	if (!newlst)
		return ;
	if (*lst == NULL)
		*lst = newlst;
	else
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = newlst;
	}
}
