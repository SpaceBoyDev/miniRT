/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:39 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 01:33:14 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include "../../include/parse.h"

static bool	check_file_extension(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
		++i;
	if (arg[i - 1] != 't' || arg[i - 2] != 'r' || arg[i - 3] != '.')
		return (false);
	return (true);
}

static int	parse_line(char *line)
{
	if (!ft_strncmp(line, ID_AMBIENT, 2))
		parse_ambient(line);
	else if (!ft_strncmp(line, ID_CAMERA, 2))
		parse_camera(line);
	else if (!ft_strncmp(line, ID_LIGHT, 2))
		return (parse_light(line));
	else if (!ft_strncmp(line, ID_SPHERE, 3))
		return (parse_sphere(line));
	else if (!ft_strncmp(line, ID_PLANE, 3))
		return (parse_plane(line));
	else if (!ft_strncmp(line, ID_CYL, 3))
		return (parse_cylinder(line));
	else
		return (ERR_OBJ_ID);
	return (OK);
}

int	parse_file(char *file)
{
	int		fd;
	char	*line;

	if (!check_file_extension(file))
		return (ERR_EXTENSION);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ERR_OPEN);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strncmp(line, "\n", 1) != 0)
			parse_line(line);
		free(line);
	}
	return (OK);
}
