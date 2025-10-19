/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:37:58 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 00:23:19 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int	parse_file(char *file);
int	parse_line(char *line);

int	parse_ambient(char *line);
int	parse_camera(char *line);
int	parse_light(char *line);
int	parse_sphere(char *line);
int	parse_plane(char *line);
int	parse_cylinder(char *line);

#endif