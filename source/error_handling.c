/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by dario             #+#    #+#             */
/*   Updated: 2025/10/22 21:01:01 by dario            ###   ########.fr       */
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
	"Trash at the end of the line.\n"\
	"Object should only have their own atributes.",
	"Duplicated ambient lighting.",
	"The given ratio is not valid.",
	"The given color is not valid.",
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

void	free_scene(t_scene *scene)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
	while (scene->sphere_list)
	{
		free(scene->sphere_list);
		++scene->sphere_list;
	}
	while (scene->plane_list)
	{
		free(scene->plane_list);
		++scene->plane_list;
	}
	while (scene->cylinder_list)
	{
		free(scene->cylinder_list);
		++scene->cylinder_list;
	}

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
