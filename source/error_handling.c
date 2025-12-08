/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:51:46 by dario             #+#    #+#             */
/*   Updated: 2025/12/08 23:56:57 by dario            ###   ########.fr       */
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
	"Light line has invalid values at the end."
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
	"Cone coordinates are not valid.",
	"Cone axis is not valid.",
	"Cone diameter is not valid.",
	"Cone height is not valid.",
	"Cone color is not valid.",
	"Cone line has invalid values at the end.",
	"MLX failed to initialize.",
	"MLX failed to add hook.",
	"MLX failed to create image.",
	"MLX failed to render the image to the window."
};

void	print_error(t_error error)
{
	if (error == OK)
		return ;
	ft_printf(RED "Error: %s" RST "\n", g_message[error]);
}

void	exit_error(t_error error, t_scene *scene)
{
	if (scene)
		free_scene(scene);
	print_error(error);
	exit (error);
}
