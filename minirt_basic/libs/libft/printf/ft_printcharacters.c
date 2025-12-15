/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printcharacters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darmarti <darmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:18:22 by dario             #+#    #+#             */
/*   Updated: 2024/12/03 17:36:24 by darmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *s, int *len)
{
	if (!s)
		return (ft_putstr("(null)", len));
	while (*s)
	{
		ft_putchar(*s, len);
		++s;
	}
}

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	++(*len);
}
