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

	sphere = (t_sphere *)init_obj(scene, SPHERE);
	line += 2;
	line = skip_blank(line);
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

	plane = (t_plane *)init_obj(scene, PLANE);
	line += 2;
	line = skip_blank(line);
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

	cylinder = (t_cylinder *)init_obj(scene, CYLINDER);
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
	
	cone = (t_cone *)init_obj(scene, CONE);
	line += 2;
	line = skip_blank(line);
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

int	parse_paraboloid(char *line, t_scene *scene)
{
	t_paraboloid	*paraboloid;

	paraboloid = (t_paraboloid *)init_obj(scene, PARABOLOID); 
	if (!paraboloid)
		return (ERR_ALLOC);
	
	line += 2;
	line = skip_blank(line);

	line = parse_coords(line, &paraboloid->position);
	if (!line)
		return (ERR_PB_COORDS);

	line = parse_normalized_vector(line, &paraboloid->axis);
	if (!line)
		return (ERR_PB_AXIS);

	line = parse_double(line, &paraboloid->k_factor);
	if (!line || paraboloid->k_factor <= 0.0) // k_factor debe ser positivo
		return (ERR_PB_FACTOR);
	
	line = parse_double(line, &paraboloid->h_limit);
	if (!line || paraboloid->h_limit <= 0.0) // H debe ser positivo
		return (ERR_PB_LIMIT);

	line = parse_color(line, &paraboloid->color);
	if (!line)
		return (ERR_PB_COLOR);
	
	if (!check_trash_line(line))
		return (ERR_PB_TRASH);

	return (OK);
}

int	parse_hyperboloid(char *line, t_scene *scene)
{
	t_hyperboloid	*hyperboloid;

	hyperboloid = (t_hyperboloid *)init_obj(scene, HYPERBOLOID);
	if (!hyperboloid)
		return (ERR_ALLOC);
	line += 2;
	line = skip_blank(line);
	line = parse_coords(line, &hyperboloid->position);
	if (!line)
		return (ERR_HB_COORDS);
	line = parse_normalized_vector(line, &hyperboloid->axis);
	if (!line)
		return (ERR_HB_AXIS);
	line = parse_double(line, &hyperboloid->a_param);
	if (!line || hyperboloid->a_param <= 0.0)
		return (ERR_HB_APARAM);
	line = parse_double(line, &hyperboloid->b_param);
	if (!line || hyperboloid->b_param <= 0.0)
		return (ERR_HB_BPARAM);
	line = parse_double(line, &hyperboloid->c_param);
	if (!line || hyperboloid->c_param <= 0.0)
		return (ERR_HB_CPARAM);
	line = parse_double(line, &hyperboloid->h_limit);
	if (!line || hyperboloid->h_limit <= 0.0)
		return (ERR_HB_LIMIT);
	line = parse_color(line, &hyperboloid->color);
	if (!line)
		return (ERR_HB_COLOR);
	if (!check_trash_line(line))
		return (ERR_HB_TRASH);
	return (OK);
}
