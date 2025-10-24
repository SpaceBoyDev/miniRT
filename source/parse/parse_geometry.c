/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 01:29:44 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 06:16:21 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (ERR_ALLOC);
	if (!scene->sphere_list)
		sphere->next = NULL;
	else
		sphere->next = scene->sphere_list;
	scene->sphere_list = sphere;
	line += 2;
	line = skip_blank(line);
	line = parse_coords(line, &sphere->position);
	if (!line)
		return (ERR_SPHERE_COORDS);
	line = parse_double(line, &sphere->diameter);
	if (!line)
		return (ERR_SPHERE_DIAMETER);
	line = parse_color(line, &sphere->color);
	if (!line)
		return (ERR_SPHERE_COLOR);
	if (!check_trash_line(line))
		return (ERR_SPHERE_TRASH);
	return (OK);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (ERR_ALLOC);
	if (!scene->plane_list)
		plane->next = NULL;
	else
		plane->next = scene->plane_list;
	scene->plane_list = plane;
	line += 2;
	line = skip_blank(line);
	line = parse_coords(line, &plane->position);
	if (!line)
		return (ERR_PLANE_COORDS);
	line = parse_normalized_vector(line, &plane->normal);
	if (!line)
		return (ERR_PLANE_NORMAL);
	line = parse_color(line, &plane->color);
	if (!line)
		return (ERR_PLANE_COLOR);
	if (!check_trash_line(line))
		return (ERR_PLANE_TRASH);
	return (OK);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (ERR_ALLOC);
	if (!scene->cylinder_list)
		cylinder->next = NULL;
	else
		cylinder->next = scene->cylinder_list;
	scene->cylinder_list = cylinder;
	line += 2;
	line = skip_blank(line);
	line = parse_coords(line, &cylinder->position);
	if (!line)
		return (ERR_CYL_COORDS);
	line = parse_normalized_vector(line, &cylinder->axis);
	if (!line)
		return (ERR_CYL_AXIS);
	line = parse_double(line, &cylinder->diameter);
	if (!line)
		return (ERR_CYL_DIAMETER);
	line = parse_double(line, &cylinder->height);
	if (!line)
		return (ERR_CYL_HEIGHT);
	line = parse_color(line, &cylinder->color);
	if (!line)
		return (ERR_CYL_COLOR);
	if (!check_trash_line(line))
		return (ERR_CYL_TRASH);
	return (OK);
}
