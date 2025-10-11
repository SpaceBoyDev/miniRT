/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:46:12 by dario             #+#    #+#             */
/*   Updated: 2024/09/27 20:23:34 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	const char	*aux;
	size_t		count;

	aux = s;
	count = 0;
	while (*aux)
	{
		while (*aux == c && *aux != '\0')
			++aux;
		if (*aux)
		{
			++count;
			while (*aux && (*aux != c))
				++aux;
		}
	}
	return (count);
}

static char	**ft_freesplit(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	*ft_allocword(char const *start, size_t len)
{
	char	*word;

	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t		word_count;
	size_t		i;
	char		**split;
	const char	*start;

	if (!s)
		return (NULL);
	word_count = ft_countwords(s, c);
	split = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		while (*s == c && *s)
			++s;
		start = s;
		while (*s && *s != c)
			++s;
		split[i] = ft_allocword(start, (s - start));
		if (!split[i])
			return (ft_freesplit(split, i));
	}
	split[i] = NULL;
	return (split);
}
