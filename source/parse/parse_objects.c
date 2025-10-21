/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:21:49 by dario             #+#    #+#             */
/*   Updated: 2025/10/21 17:58:33 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse_ambient(char *line, t_scene *scene)
{
	printf("%s\n", __func__);
	printf("%s", line);
	int	i;

	if (scene->ambient)
		return (ERR_DUP_AMB);
	scene->ambient = malloc(sizeof(t_ambient));
	i = 1;
	if (!parse_ratio(&line[i], &scene->ambient->lighting))
		return (ERR_BAD_DOUBLE);
	printf("Ratio: %f\n", scene->ambient->lighting);
	
	// Parse double parse_double(line[i])
	// Parse vector parse_vector(line[i])
	// Check there isn't anything else check(line[i])
	return (OK);
}

int	parse_camera(char *line, t_scene *scene)
{
	printf("%s\n", __func__);
	printf("%s", line);
	(void)scene;
	return (OK);
}

int	parse_light(char *line, t_scene *scene)
{
	printf("%s\n", __func__);
	printf("%s", line);
	(void)scene;
	return (OK);
}
