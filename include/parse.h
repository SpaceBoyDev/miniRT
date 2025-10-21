/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:37:58 by dario             #+#    #+#             */
/*   Updated: 2025/10/21 17:35:25 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "miniRT.h"

// parse_atributes.c
bool	parse_ratio(char *str, double *result);

// parse_vars.c
bool	parse_double(char *str, double *result);

// parse_file.c
char	*advance_until_char(char *str, int *i);
int		parse_file(char *file, t_scene *scene);

// parse_geometry.c
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);

// parse_objects.c
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);

#endif