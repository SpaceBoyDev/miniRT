/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darmarti <darmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:39 by dario             #+#    #+#             */
/*   Updated: 2025/12/16 11:51:35 by darmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include "../../include/parse.h"

static void	finish_free_gnl(char *line, int fd)
{
	if (!line)
		return ;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

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

static int	parse_line(char *line, t_scene *scene)
{
	int	(*parse_type)(char *, t_scene *);

	if (!ft_strncmp(line, ID_AMBIENT, 2))
		parse_type = parse_ambient;
	else if (!ft_strncmp(line, ID_CAMERA, 2))
		parse_type = parse_camera;
	else if (!ft_strncmp(line, ID_LIGHT, 2))
		parse_type = parse_light;
	else if (!ft_strncmp(line, ID_SPHERE, 3))
		parse_type = parse_sphere;
	else if (!ft_strncmp(line, ID_PLANE, 3))
		parse_type = parse_plane;
	else if (!ft_strncmp(line, ID_CYL, 3))
		parse_type = parse_cylinder;
	else
		return (ERR_OBJ_ID);
	return (parse_type(line, scene));
}

char	*advance_until_char(char *str, int *i)
{
	if (!str)
		return (0);
	while (str[*i] && str[*i] != ' ')
		++(*i);
	return (&str[*i + 1]);
}

int	parse_file(char *file, t_scene *scene)
{
	int		fd;
	int		error;
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
		{
			error = parse_line(line, scene);
			if (error != 0)
				return (finish_free_gnl(line, fd), exit_error(error, scene), 0);
		}
		free(line);
	}
	return (OK);
}
