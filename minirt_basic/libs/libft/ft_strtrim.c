/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:04:37 by dario             #+#    #+#             */
/*   Updated: 2024/09/27 20:05:37 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findchars(char const c, char const *find)
{
	while (*find)
	{
		if (c == *find)
			return (0);
		++find;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_findchars(s1[start], set) == 0)
		++start;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_findchars(s1[end], set) == 0)
		--end;
	++end;
	trim = ft_calloc((end - start + 1), sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		trim[i] = s1[start + i];
		++i;
	}
	return (trim);
}
