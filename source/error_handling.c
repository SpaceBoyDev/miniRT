/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by dario             #+#    #+#             */
/*   Updated: 2025/10/23 20:49:38 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static const char	*g_message[MAX_ERR_CODE] = {
	"",
	"Could not allocate memory.",
	"You must input a .rt file as the single argument.\n"\
	"How to execute: './miniRT <file.rt>'.",
	"The scene file must have the .rt extension.",
	"Could not open file.",
	"Wrong scene object identifier.",
	"Duplicated ambient lighting.",
	"Duplicated camera.",
	"Duplicated light.",
	"Ambient ratio is not valid.",
	"Ambient color is not valid.",
	"Ambient line has invalid values at the end.",
	"Camera coordinates are not valid.",
	"Camera orientation is not valid.",
	"Camera FOV is not valid.",
	"Camera line has invalid values at the end.",
	"Light coordinates are not valid.",
	"Light ratio is not valid.",
	"Light color is not valid.",
	"Light line has invalid values at the end.",
	"Sphere coordinates are not valid.",
	"Sphere diameter is not valid.",
	"Sphere color is not valid.",
	"Sphere line has invalid values at the end.",
	"Plane coordinates are not valid.",
	"Plane normal is not valid.",
	"Plane color is not valid.",
	"Plane line has invalid values at the end.",
	"Cylinder coordinates are not valid.",
	"Cylinder axis is not valid.",
	"Cylinder diameter is not valid.",
	"Cylinder height is not valid.",
	"Cylinder color is not valid.",
	"Cylinder line has invalid values at the end.",
};

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

	while (scene->sphere_list)
	{
		next = scene->sphere_list->next;
		free(scene->sphere_list);
		scene->sphere_list = next;
	}
	while (scene->plane_list)
	{
		next = scene->plane_list->next;
		free(scene->plane_list);
		scene->plane_list = next;
	}
	while (scene->cylinder_list)
	{
		next = scene->cylinder_list->next;
		free(scene->cylinder_list);
		scene->cylinder_list = next;
	}
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

void	print_error(t_error error)
{
	if (error == OK)
		return ;
	printf(RED "Error: %s" RST "\n", g_message[error]);
}

void	exit_error(t_error error, t_scene *scene)
{
	if (error == OK)
		return ;
	if (scene)
		free_scene(scene);
	print_error(error);
	exit (error);
}
