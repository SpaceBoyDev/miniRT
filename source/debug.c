/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:28:53 by dario             #+#    #+#             */
/*   Updated: 2025/12/09 14:29:30 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	print_data(t_scene *scene)
{
	if (scene->ambient)
	{
		printf("\n\tAMBIENT\n");
		printf("Color %f %f %f\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
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
	
	t_obj	*obj = scene->objs;
	while (obj)
	{
		if (obj->id == SPHERE)
		{
			t_sphere sphere = obj->geo->sphere; 
			printf("\n\tSPHERE\n");
			printf("Diameter %f\n", sphere.diameter);
			printf("Coords %f %f %f\n", sphere.position.x, sphere.position.y, sphere.position.z);
			printf("Color %f %f %f\n", sphere.color.r, sphere.color.g, sphere.color.b);
		}
		else if (obj->id == PLANE)
		{
			t_plane plane = obj->geo->plane;
			printf("\n\tPLANE\n");
			printf("Coords %f %f %f\n", plane.position.x, plane.position.y, plane.position.z);
			printf("Normal %f %f %f\n", plane.normal.x, plane.normal.y, plane.normal.z);
			printf("Color %f %f %f\n", plane.color.r, plane.color.g, plane.color.b);
		}
		else if (obj->id == CYLINDER)
		{
			t_cylinder cylinder = obj->geo->cylinder;
			printf("\n\tCYLINDER\n");
			printf("Coords %f %f %f\n", cylinder.position.x, cylinder.position.y, cylinder.position.z);
			printf("Axis %f %f %f\n", cylinder.axis.x, cylinder.axis.y, cylinder.axis.z);
			printf("Diameter %f\n", cylinder.diameter);
			printf("Height %f\n", cylinder.height);
			printf("Color %f %f %f\n", cylinder.color.r, cylinder.color.g, cylinder.color.b);
		}
		obj = obj->next;
	}
}
