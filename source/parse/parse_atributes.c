/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:20:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/23 19:37:01 by dario            ###   ########.fr       */
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
	printf("===RATIO===\n");
	printf("Ratio -> %f\n", *result);
	return (++str);
}

char	*parse_color(char *str, t_color *result)
{
	if (!str)
		return (NULL);
	str = read_int_vector(str, result);
	if (!str)
		return (NULL);
	printf("===Color===\n");
	printf("R -> %i\n", result->r);
	printf("G -> %i\n", result->g);
	printf("B -> %i\n", result->b);
	if (result->r > 255 || result->r < 0
		|| result->g > 255 || result->g < 0
		|| result->b > 255 || result->b < 0)
		return (NULL);

	return (str);
}

char	*parse_coords(char *str, t_coords *result)
{
	if (!str)
		return (NULL);
	str = read_double_vector(str, &result->x, &result->y, &result->z);
	if (!str)
		return (NULL);
	printf("===Position===\n");
	printf("X -> %f\n", result->x);
	printf("Y -> %f\n", result->y);
	printf("Z -> %f\n", result->z);
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
	printf("===Orientation===\n");
	printf("X -> %f\n", result->x);
	printf("Y -> %f\n", result->y);
	printf("Z -> %f\n", result->z);
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
	printf("===FOV===\n");
	printf("FOV -> %i\n", *result);
	return (str);
}
