/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 14:10:38 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

int	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	color = 0;

	int increment = 50;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			t_ray ray = generate_ray(data->scene->camera, x, y, WIN_WIDTH, WIN_HEIGHT);
			t_color color = trace_ray(&ray, data->scene);
			mlx_put_pixel(data->img, x, y, rgb_to_uint(&color));
			++y;
		}
		color += increment;
		++x;
	}

	return (OK);
}
