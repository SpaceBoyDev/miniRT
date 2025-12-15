/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:27:30 by darmarti          #+#    #+#             */
/*   Updated: 2024/09/24 20:25:51 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			size;
	unsigned char	*str;

	size = 0;
	str = s;
	while (size < n)
	{
		*str = (unsigned char) c;
		++str;
		++size;
	}
	return (s);
}
