/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:21:49 by dario             #+#    #+#             */
/*   Updated: 2025/10/22 20:46:13 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse_ambient(char *line, t_scene *scene)
{
	printf("%s\n", __func__);
	if (scene->ambient)
		return (ERR_DUP_AMB);
	scene->ambient = malloc(sizeof(t_ambient));
	++line;
	while (*line && *line == ' ')
		++line;
	line = parse_ratio(line, &scene->ambient->lighting);
	if (!line)
		return (ERR_BAD_RATIO);
	printf("Ratio: %f\n", scene->ambient->lighting);
	while (*line && *line == ' ')
		++line;
	line = parse_color(line, &scene->ambient->color);
	if (!line)
		return (ERR_BAD_COLOR);
	printf("linea restante -> %s\n", line);
	if (!check_trash_line(line))
		return (ERR_TRASH_LINE);
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
