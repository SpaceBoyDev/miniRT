/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:19 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 06:14:52 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/miniRT.h"
#include "../include/parse.h"

void	print_data(t_scene *scene)
{
	if (scene->ambient)
	{
		printf("\n\tAMBIENT\n");
		printf("Color %i %i %i\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
		printf("Ratio %f\n", scene->ambient->lighting);
	}
	if (scene->camera)
	{
		printf("\n\tCAMERA\n");
		printf("Coords %f %f %f\n", scene->camera->position.x, scene->camera->position.y, scene->camera->position.z);
		printf("Direction %f %f %f\n", scene->camera->orientation.x, scene->camera->orientation.y, scene->camera->orientation.z);
		printf("FOV %i\n", scene->camera->fov);
	}
	if (scene->light)
	{
		printf("\n\tLIGHT\n");
		printf("Coords %f %f %f\n", scene->light->position.x, scene->light->position.y, scene->light->position.z);
		printf("Ratio %f\n", scene->light->brightness);
	}
	t_plane *plane = scene->plane_list;
	while (plane)
	{
		printf("\n\tPLANE\n");
		printf("Coords %f %f %f\n", plane->position.x, plane->position.y, plane->position.z);
		printf("Normal %f %f %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
		printf("Color %i %i %i\n", plane->color.r, plane->color.g, plane->color.b);
		plane = plane->next;
	}
	t_sphere *sphere = scene->sphere_list;
	while (sphere)
	{
		printf("\n\tSPHERE\n");
		printf("Coords %f %f %f\n", sphere->position.x, sphere->position.y, sphere->position.z);
		printf("Diameter %f\n", sphere->diameter);
		printf("Color %i %i %i\n", sphere->color.r, sphere->color.g, sphere->color.b);
		sphere = sphere->next;
	}
	t_cylinder *cylinder = scene->cylinder_list;
	while (cylinder)
	{
		printf("\n\tCYLINDER\n");
		printf("Coords %f %f %f\n", cylinder->position.x, cylinder->position.y, cylinder->position.z);
		printf("Axis %f %f %f\n", cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
		printf("Diameter %f\n", cylinder->diameter);
		printf("Height %f\n", cylinder->height);
		printf("Color %i %i %i\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
		cylinder = cylinder->next;
	}
}

void test_error_codes()
{
	int	i;

	i = -1;
	while (++i < MAX_ERR_CODE)
	{
		printf("Error nº%i\n", i);
		print_error(i);
		printf("\n");
	}
}

void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere_list = NULL;
	scene->plane_list = NULL;
	scene->cylinder_list = NULL;
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	test_error_codes();
	init_scene(&scene);
	if (argc != 2)
		exit_error(ERR_ARGS, NULL);
	exit_error(parse_file(argv[1], &scene), &scene);
	//print_data(&scene);
	free_scene(&scene);
	return (OK);
}
