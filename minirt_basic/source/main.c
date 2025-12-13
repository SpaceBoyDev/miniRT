/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:19 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 20:32:05 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "../include/miniRT.h"
#include "../include/parse.h"
#include "../include/mlx.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_scene	scene;
	t_error	status;

	if (argc != 2)
		exit_error(ERR_ARGS, NULL);
	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	data.scene = &scene;
	status = parse_file(argv[1], data.scene);
	if (status != OK)
		exit_error(status, data.scene);
	status = initialize_mlx(&data);
	if (status != OK)
		exit_error(status, data.scene);
	free_scene(data.scene);
	return (OK);
}
