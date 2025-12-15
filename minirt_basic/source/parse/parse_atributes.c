/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:20:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 21:53:58 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*parse_ratio(char *str, double *result)
{
	if (!str)
		return (NULL);
	str = read_double(str, result);
	if (!str)
		return (NULL);
	if (*result > 1.0 || *result < 0.0)
		return (NULL);
	str = skip_blank(str);
	return (str);
}

char	*parse_double(char *str, double *result)
{
	if (!str)
		return (NULL);
	str = read_double(str, result);
	if (!str)
		return (NULL);
	str = skip_blank(str);
	return (str);
}

char	*parse_fov(char *str, int *result)
{
	if (!str)
		return (NULL);
	*result = ft_atoi(str);
	if (*result < 0 || *result > 180)
		return (NULL);
	while (*str && (ft_isdigit(*str) || *str == '+' || *str == '-'))
		++str;
	str = skip_blank(str);
	return (str);
}
