/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:25:23 by darmarti          #+#    #+#             */
/*   Updated: 2025/01/09 18:26:13 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_null(char **buffer, char **new_line)
{
	if (*new_line)
	{
		free(*new_line);
		*new_line = NULL;
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

static void	ft_clean(char *line, char *clean_line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i])
	{
		clean_line[i] = line[i];
		++i;
	}
	if (line[i] == '\n')
		clean_line[i] = '\n';
	else
		clean_line[i] = '\0';
}

static char	*ft_cleanline(char *line, char **last_buffer)
{
	char	*clean_line;
	size_t	i;

	i = 0;
	if (line[0] == '\0')
	{
		if (*last_buffer)
		{
			free(*last_buffer);
			*last_buffer = NULL;
		}
		free(line);
		line = NULL;
		return (NULL);
	}
	while (line[i] != '\n' && line[i])
		++i;
	clean_line = (char *)calloc_gnl(i + 2, sizeof(char));
	if (!clean_line)
		return (free(line), NULL);
	ft_clean(line, clean_line);
	free(line);
	line = NULL;
	return (clean_line);
}

static char	*ft_clean_last_buffer(char *buffer) //DA PROBLEMAS
{
	char	*new_last_buffer;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (NULL);
	len = strlen_gnl(buffer);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		++i;
	if (buffer[i] == '\n')
		++i;
	new_last_buffer = calloc_gnl((len - i + 1), sizeof(char));
	if (!new_last_buffer)
		return (NULL);
	j = 0;
	while (buffer[i] != '\0')
		new_last_buffer[j++] = buffer[i++];
	free(buffer);
	buffer = NULL;
	return (new_last_buffer);
}

char	*get_next_line(int fd)
{
	static char		*all_lines[1024];
	char			*line;
	char			*buff;
	int				bytes_read;

	if (!all_lines[fd])
		all_lines[fd] = calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	buff = (char *)calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || !buff || !all_lines[fd])
		return (ft_null(&buff, &all_lines[fd]));
	line = strjoin_gnl(NULL, all_lines[fd]);
	bytes_read = 1;
	while (!strchr_gnl(buff, '\n') && bytes_read > 0 && !strchr_gnl(line, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), line = NULL, ft_null(&buff, &all_lines[fd]));
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		line = strjoin_gnl(line, buff);
		all_lines[fd] = strjoin_gnl(all_lines[fd], buff);
	}
	all_lines[fd] = ft_clean_last_buffer(all_lines[fd]);
	return (line = ft_cleanline(line, &all_lines[fd]), free(buff), line);
}
