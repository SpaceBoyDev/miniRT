/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darmarti <darmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by dario             #+#    #+#             */
/*   Updated: 2025/12/16 11:24:08 by darmarti         ###   ########.fr       */
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
	mlx_terminate(data->mlx);
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

void	free_all(t_data *data)
{
	free_scene(data->scene);
	free_data(data);
}
