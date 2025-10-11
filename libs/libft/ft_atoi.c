/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:03:27 by darmarti          #+#    #+#             */
/*   Updated: 2025/06/10 20:32:06 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	negative;

	num = 0;
	negative = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		++nptr;
	if (*nptr == '-')
	{
		if (!ft_isdigit(*(nptr + 1)))
			return (0);
		negative = -1;
		++nptr;
	}
	if (*nptr == '+' && ft_isdigit(*(nptr + 1)))
		++nptr;
	else if (*nptr == '+' && !ft_isdigit(*(nptr + 1)))
		return (0);
	while (ft_isdigit(*nptr))
	{
		num = (num * 10) + ((int)*nptr - '0');
		++nptr;
	}
	return (num * negative);
}
