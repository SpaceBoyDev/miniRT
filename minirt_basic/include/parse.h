/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:37:58 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 18:41:58 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "miniRT.h"

// parse_atributes.c
char	*parse_ratio(char *str, double *result);
char	*parse_double(char *str, double *result);
char	*parse_fov(char *str, int *result);

// parse_vector_atributes.c
char	*parse_color(char *str, t_color *result);
char	*parse_coords(char *str, t_coords *result);
char	*parse_normalized_vector(char *str, t_coords *vector);

// parse_file.c
char	*advance_until_char(char *str, int *i);
int		parse_file(char *file, t_scene *scene);

// parse_geometry.c
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_cone(char *line, t_scene *scene);
int		parse_paraboloid(char *line, t_scene *scene);
int		parse_hyperboloid(char *line, t_scene *scene);
char	*line_advance_and_init(t_scene *scene, \
char *line, int obj_type, void **obj);

// parse_objects.c
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);

// parse_utils.c
void	*init_obj(t_scene *scene, t_id id);
char	*skip_blank(char *str);
int		table_len(char **table);
bool	is_number(char *str);
bool	check_trash_line(char *str);

// parse_vars.c
char	*read_double(char *str, double *result);

// parse_vector_vars.c
char	*read_int_vector(char *str, t_color *scene);
char	*read_double_vector(char *str, double *x, double *y, double *z);

#endif
