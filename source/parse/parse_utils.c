/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:14:52 by dario             #+#    #+#             */
/*   Updated: 2025/10/28 20:55:56 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	*init_obj(t_scene *scene, t_id id)
{
	t_obj	*new_obj;
	void	*new_geo;

	new_obj = malloc(sizeof(t_obj));
	new_geo = malloc(sizeof(t_geo));
	if (!new_geo || !new_obj)
		return (NULL);
	new_obj->id = id;
	new_obj->geo = new_geo;
	new_obj->next = NULL;
	if (!scene->objs)
		new_obj->next = NULL;
	else
		new_obj->next = scene->objs;
	scene->objs = new_obj;
	return (new_geo);
}

char	*skip_blank(char *str)
{
	while (*str && *str == ' ')
		++str;
	return (str);
}

int	table_len(char **table)
{
	int	len;

	len = 0;
	while (table[len])
		++len;
	return (len);
}

bool	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		++i;
	}
	return (true);
}

bool	check_trash_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\n')
			return (false);
		++str;
	}
	return (true);
}
