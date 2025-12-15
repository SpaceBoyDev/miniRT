/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:45:49 by darmarti          #+#    #+#             */
/*   Updated: 2024/09/27 17:15:08 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		i;

	ptr = malloc(nmemb * size);
	i = 0;
	if (ptr == NULL)
		return (0);
	while (i < nmemb * size)
	{
		((unsigned char *)ptr)[i] = '\0';
		++i;
	}
	return ((unsigned char *)ptr);
}
