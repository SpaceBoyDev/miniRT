/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:33:09 by dario             #+#    #+#             */
/*   Updated: 2025/03/28 20:32:44 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*node;

	node = malloc(1 * sizeof(t_lst));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
