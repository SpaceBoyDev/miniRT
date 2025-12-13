/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:12:42 by dario             #+#    #+#             */
/*   Updated: 2024/09/27 18:03:26 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if ((start + len) > s_len)
		len = s_len - start;
	i = 0;
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		++i;
	}
	return (substr);
}
