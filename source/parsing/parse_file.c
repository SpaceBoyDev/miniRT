/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:39 by dario             #+#    #+#             */
/*   Updated: 2025/10/20 00:59:37 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include "../../include/parsing.h"
#include "../../include/miniRT.h"

bool	check_file_extension(char *arg);

int		parse_file(char *file)
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

bool	check_file_extension(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
		++i;
	if (arg[i - 1] != 't' || arg[i - 2] != 'r' || arg[i - 3] != '.')
		return (false);
	return (true);
}
