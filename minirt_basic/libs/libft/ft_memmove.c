/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:54:52 by darmarti          #+#    #+#             */
/*   Updated: 2024/09/24 23:26:31 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*aux_dest;
	const unsigned char	*aux_src;
	size_t				i;

	aux_dest = (unsigned char *)dest;
	aux_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (aux_dest > aux_src)
		while (n-- > 0)
			aux_dest[n] = aux_src[n];
	else
	{
		while (i < n)
		{
			aux_dest[i] = aux_src[i];
			++i;
		}
	}
	return (dest);
}
