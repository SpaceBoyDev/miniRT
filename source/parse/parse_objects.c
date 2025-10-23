/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:21:49 by dario             #+#    #+#             */
/*   Updated: 2025/10/23 03:32:22 by dario            ###   ########.fr       */
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
	line = skip_blank(line);
	line = parse_ratio(line, &scene->ambient->lighting);
	if (!line)
		return (ERR_BAD_RATIO);
	line = skip_blank(line);
	line = parse_color(line, &scene->ambient->color);
	if (!line)
		return (ERR_BAD_COLOR);
	if (!check_trash_line(line))
		return (ERR_TRASH_LINE);
	return (OK);
}

int	parse_camera(char *line, t_scene *scene)
{
	printf("%s\n", __func__);
	if (scene->camera)
		return (ERR_DUP_CAM);
	scene->camera = malloc(sizeof(t_camera));
	++line;
	line = skip_blank(line);
	line = parse_coords(line, &scene->camera->position);
	if (!line)
		return (ERR_BAD_COORDS);
	line = skip_blank(line);
	line = parse_normalized_vector(line, &scene->camera->orientation);
	if (!line)
		return (ERR_BAD_ORIENTATION);
	return (OK);
}

int	parse_light(char *line, t_scene *scene)
{
	printf("%s\n", __func__);
	if (scene->light)
		return (ERR_DUP_LIGHT);
	scene->light = malloc(sizeof(t_light));
	++line;
	line = skip_blank(line);
	line = parse_coords(line, &scene->light->position);
	if (!line)
		return (ERR_BAD_COORDS);
	line = skip_blank(line);
	line = parse_ratio(line, &scene->light->brightness);
	if (!line)
		return (ERR_BAD_RATIO);
	line = skip_blank(line);
	line = parse_color(line, &scene->light->color);
	if (!line)
		return (ERR_BAD_COLOR);
	if (!check_trash_line(line))
		return (ERR_TRASH_LINE);
	return (OK);
}
