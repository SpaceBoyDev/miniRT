/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:09:19 by dario             #+#    #+#             */
/*   Updated: 2025/12/09 14:32:38 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "../include/miniRT.h"
#include "../include/parse.h"
#include "../include/mlx.h"

void	test_error_codes(void)
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_scene	scene;
	t_fps	fps;
	t_error	status;

	if (argc != 2)
		exit_error(ERR_ARGS, NULL);
	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	ft_memset(&fps, 0, sizeof(t_fps));
	data.scene = &scene;
	data.fps = &fps;
	status = parse_file(argv[1], data.scene);
	if (status != OK)
		exit_error(status, data.scene);
	if (DEBUG)
		print_data(data.scene);
	status = initialize_mlx(&data);
	if (status != OK)
		exit_error(status, data.scene);
	free_scene(data.scene);
	return (OK);
}
