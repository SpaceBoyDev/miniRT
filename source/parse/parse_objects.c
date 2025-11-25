/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:21:49 by dario             #+#    #+#             */
/*   Updated: 2025/11/26 00:16:49 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse_ambient(char *line, t_scene *scene)
{
	if (scene->ambient)
		return (ERR_DUP_AMB);
	scene->ambient = malloc(sizeof(t_ambient));
	if (!scene->ambient)
		return (ERR_ALLOC);
	++line;
	line = skip_blank(line);
	line = parse_ratio(line, &scene->ambient->lighting);
	if (!line)
		return (ERR_AMB_RATIO);
	line = parse_color(line, &scene->ambient->color);
	scene->ambient->color.r = scene->ambient->color.r / 255.0;
	scene->ambient->color.g = scene->ambient->color.g / 255.0;
	scene->ambient->color.b = scene->ambient->color.b / 255.0;
	if (!line)
		return (ERR_AMB_COLOR);
	if (!check_trash_line(line))
		return (ERR_AMB_TRASH);
	return (OK);
}

int	parse_camera(char *line, t_scene *scene)
{
	if (scene->camera)
		return (ERR_DUP_CAM);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (ERR_ALLOC);
	++line;
	line = skip_blank(line);
	line = parse_coords(line, &scene->camera->position);
	if (!line)
		return (ERR_CAM_COORDS);
	line = parse_normalized_vector(line, &scene->camera->orientation);
	if (!line)
		return (ERR_CAM_ORIENTATION);
	line = parse_fov(line, &scene->camera->fov);
	if (!line)
		return (ERR_CAM_FOV);
	if (!check_trash_line(line))
		return (ERR_CAM_TRASH);
	return (OK);
}

int	parse_light(char *line, t_scene *scene)
{
	if (scene->light)
		return (ERR_DUP_LIGHT);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		return (ERR_ALLOC);
	++line;
	line = skip_blank(line);
	line = parse_coords(line, &scene->light->position);
	if (!line)
		return (ERR_LIGHT_COORDS);
	line = skip_blank(line);
	line = parse_ratio(line, &scene->light->brightness);
	if (!line)
		return (ERR_LIGHT_RATIO);
	line = skip_blank(line);
	line = parse_color(line, &scene->light->color);
	scene->light->color.r = scene->light->color.r / 255.0;
	scene->light->color.g = scene->light->color.g / 255.0;
	scene->light->color.b = scene->light->color.b / 255.0;
	if (!line)
		return (ERR_LIGHT_COLOR);
	if (!check_trash_line(line))
		return (ERR_LIGHT_TRASH);
	return (OK);
}
