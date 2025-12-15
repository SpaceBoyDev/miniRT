/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:42:59 by dario             #+#    #+#             */
/*   Updated: 2025/09/12 14:59:27 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	assing_len(char const *s1, char const *s2, size_t *l1, size_t *l2)
{
	*l1 = ft_strlen(s1);
	*l2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	i = 0;
	assing_len(s1, s2, &s1_len, &s2_len);
	str = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		++i;
	}
	while (i < (s1_len + s2_len))
	{
		str[i] = s2[i - s1_len];
		++i;
	}
	return (str);
}
