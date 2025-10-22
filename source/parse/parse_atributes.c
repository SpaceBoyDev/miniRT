/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:20:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/22 20:36:07 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*parse_ratio(char *str, double *result)
{
	if (!str)
		return (NULL);
	str = read_double(str, result);
	printf("str = %s\n", str);
	if (!str)
		return (NULL);
	if (*result > 1.0 || *result < 0.0)
		return (NULL);
	printf("char al final del ratio -> %c\n", *str);
	return (++str);
}

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
	printf("===Color===\n");
	printf("R -> %i\n", result->r);
	printf("G -> %i\n", result->g);
	printf("B -> %i\n", result->b);
	return (str);
}
