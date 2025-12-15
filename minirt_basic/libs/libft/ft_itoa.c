/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:08:30 by dario             #+#    #+#             */
/*   Updated: 2024/09/30 17:26:50 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t		len;
	long		aux;
	char		*str;

	len = ft_intlen(n);
	aux = n;
	str = malloc((ft_intlen(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (aux == 0)
		str[0] = '0';
	if (aux < 0)
	{
		str[0] = '-';
		aux = -aux;
	}
	str[len] = '\0';
	while (aux != 0)
	{
		--len;
		str[len] = (aux % 10) + '0';
		aux /= 10;
	}
	return (str);
}
