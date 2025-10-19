/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:56:36 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 00:28:03 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/miniRT.h"

// char	*read_obj_id(char *line)
// {
	
// }

int	parse_line(char *line)
{
	if (ft_strncmp(line, ID_AMBIENT, 1))
		return (parse_ambient(line));
	else if (ft_strncmp(line, ID_CAMERA, 1))
		parse_camera(line);
	else if (ft_strncmp(line, ID_LIGHT, 1))
		return (parse_light(line));
	else if (ft_strncmp(line, ID_SPHERE, 2))
		return (parse_sphere(line));
	else if (ft_strncmp(line, ID_PLANE, 2))
		return (parse_plane(line));
	else if (ft_strncmp(line, ID_CYL, 2))
		return (parse_cylinder(line));
	else
		return (ERR_OBJ_ID);
	return 0;
}