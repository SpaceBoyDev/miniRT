/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:21:49 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 01:31:17 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse_ambient(char *line)
{
	printf("%s\n", __func__);
	printf("%s", line);
	return (OK);
}

int	parse_camera(char *line)
{
	printf("%s\n", __func__);
	printf("%s", line);
	return (OK);
}

int	parse_light(char *line)
{
	printf("%s\n", __func__);
	printf("%s", line);
	return (OK);
}
