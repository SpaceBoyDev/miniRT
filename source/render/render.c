/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/28 20:59:43 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

int	render(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	t_color		color;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ray = generate_ray(data->scene->camera, x, y);
			color = trace_ray(&ray, data->scene);
			mlx_put_pixel(data->img, x, y, rgb_to_uint(&color));
			++y;
		}
		++x;
	}
	return (OK);
}
