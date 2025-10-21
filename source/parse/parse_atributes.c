/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:20:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/21 17:54:39 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

bool	parse_ratio(char *str, double *result)
{
	if (!parse_double(str, result))
		return (false);
	printf("estoy bieen\n");

	if (*result > 1.0 || *result < 0.0)
		return (false);
	return (true);
}