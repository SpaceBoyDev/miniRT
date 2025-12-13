/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector_atributes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 21:53:45 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 21:54:19 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*parse_color(char *str, t_color *result)
{
	if (!str)
		return (NULL);
	str = read_int_vector(str, result);
	if (!str)
		return (NULL);
	if (result->r > 255 || result->r < 0
		|| result->g > 255 || result->g < 0
		|| result->b > 255 || result->b < 0)
		return (NULL);
	str = skip_blank(str);
	return (str);
}

char	*parse_coords(char *str, t_coords *result)
{
	if (!str)
		return (NULL);
	str = read_double_vector(str, &result->x, &result->y, &result->z);
	if (!str)
		return (NULL);
	str = skip_blank(str);
	return (str);
}

char	*parse_normalized_vector(char *str, t_coords *result)
{
	if (!str)
		return (NULL);
	str = read_double_vector(str, &result->x, &result->y, &result->z);
	if (!str)
		return (NULL);
	if (result->x > 1 || result->x < -1
		|| result->y > 1 || result->y < -1
		|| result->z > 1 || result->z < -1)
		return (NULL);
	str = skip_blank(str);
	return (str);
}
