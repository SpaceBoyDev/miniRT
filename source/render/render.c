/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 20:43:51 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

int	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	t_ray 		ray;
	t_color		color;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ray = generate_ray(data->scene->camera, x, y, WIN_WIDTH, WIN_HEIGHT);
			color = trace_ray(&ray, data->scene);
			if (x == WIN_WIDTH / 2 && y == WIN_HEIGHT /2)
			{
				printf("Direccion del rayo\nx:%f y:%f z:%f\n", ray.direction.x, ray.direction.y, ray.direction.z);
				printf("Origen del rayo\nx:%f y:%f z:%f\n", ray.origin.x, ray.origin.y, ray.origin.z);
			}
			mlx_put_pixel(data->img, x, y, rgb_to_uint(&color));
			++y;
		}
		++x;
	}

	return (OK);
}
