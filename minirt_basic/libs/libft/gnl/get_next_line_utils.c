/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:25:20 by darmarti          #+#    #+#             */
/*   Updated: 2025/01/09 18:25:20 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

char	*strchr_gnl(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*calloc_gnl(size_t nmemb, size_t size)
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

void	ft_join(char *dest, const char *src, size_t *i)
{
	size_t	j;

	j = 0;
	while (src[j])
		dest[(*i)++] = src[j++];
}

char	*strjoin_gnl(char *s1, char const *s2)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s1)
		s1 = calloc_gnl(1, sizeof(char));
	if (!s2)
		s2 = calloc_gnl(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	str = malloc((strlen_gnl(s1) + strlen_gnl(s2) + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		free((char *)s2);
		return (NULL);
	}
	ft_join(str, s1, &i);
	ft_join(str, s2, &i);
	str[i] = '\0';
	free(s1);
	return (str);
}
