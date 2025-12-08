/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by dario             #+#    #+#             */
/*   Updated: 2025/12/08 23:56:43 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		++i;
	}
	free(table);
}

void	free_geometry(t_scene *scene)
{
	void	*next;

	while (scene->objs)
	{
		next = scene->objs->next;
		free(scene->objs->geo);
		free(scene->objs);
		scene->objs = next;
	}
}

void	free_data(t_data *data)
{
	free(data->mlx);
	free(data->img);
	free_scene(data->scene);
}

void	free_scene(t_scene *scene)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
	free_geometry(scene);
}
