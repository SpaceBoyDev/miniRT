/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darmarti <darmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:06:24 by darmarti          #+#    #+#             */
/*   Updated: 2024/09/25 17:29:25 by darmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	size = 0;
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j])
		{
			++size;
			++j;
			if (size > len)
				return (NULL);
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		size -= j;
		++size;
		++i;
	}
	return (NULL);
}
