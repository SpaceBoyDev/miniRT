/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 01:29:44 by dario             #+#    #+#             */
/*   Updated: 2025/11/26 00:47:14 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;

	line = line_advance_and_init(scene, line, SPHERE, (void **)&sphere);
	line = parse_coords(line, &sphere->position);
	if (!line)
		return (ERR_SPHERE_COORDS);
	line = parse_double(line, &sphere->diameter);
	if (!line)
		return (ERR_SPHERE_DIAMETER);
	line = parse_color(line, &sphere->color);
	sphere->color.r = sphere->color.r / 255.0;
	sphere->color.g = sphere->color.g / 255.0;
	sphere->color.b = sphere->color.b / 255.0;
	if (!line)
		return (ERR_SPHERE_COLOR);
	if (!check_trash_line(line))
		return (ERR_SPHERE_TRASH);
	return (OK);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	*plane;

	line = line_advance_and_init(scene, line, PLANE, (void **)&plane);
	line = parse_coords(line, &plane->position);
	if (!line)
		return (ERR_PLANE_COORDS);
	line = parse_normalized_vector(line, &plane->normal);
	if (!line)
		return (ERR_PLANE_NORMAL);
	line = parse_color(line, &plane->color);
	plane->color.r = plane->color.r / 255.0;
	plane->color.g = plane->color.g / 255.0;
	plane->color.b = plane->color.b / 255.0;
	if (!line)
		return (ERR_PLANE_COLOR);
	if (!check_trash_line(line))
		return (ERR_PLANE_TRASH);
	return (OK);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cylinder;

	line = line_advance_and_init(scene, line, CYLINDER, (void **)&cylinder);
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
	cylinder->color.r = cylinder->color.r / 255.0;
	cylinder->color.g = cylinder->color.g / 255.0;
	cylinder->color.b = cylinder->color.b / 255.0;
	if (!line)
		return (ERR_CYL_COLOR);
	if (!check_trash_line(line))
		return (ERR_CYL_TRASH);
	return (OK);
}

int	parse_cone(char *line, t_scene *scene)
{
	t_cone	*cone;

	line = line_advance_and_init(scene, line, CONE, (void **)&cone);
	line = parse_coords(line, &cone->position);
	if (!line)
		return (ERR_CONE_COORDS);
	line = parse_normalized_vector(line, &cone->axis);
	if (!line)
		return (ERR_CONE_AXIS);
	line = parse_double(line, &cone->diameter);
	if (!line)
		return (ERR_CONE_DIAMETER);
	line = parse_double(line, &cone->height);
	if (!line)
		return (ERR_CONE_HEIGHT);
	line = parse_color(line, &cone->color);
	cone->color.r = cone->color.r / 255.0;
	cone->color.g = cone->color.g / 255.0;
	cone->color.b = cone->color.b / 255.0;
	if (!line)
		return (ERR_CONE_COLOR);
	if (!check_trash_line(line))
		return (ERR_CONE_TRASH);
	return (OK);
}
