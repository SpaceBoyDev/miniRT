/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/25 20:56:35 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_ray generate_ray(t_camera cam, int x, int y, int width, int height) {
    double aspect_ratio = (double)width / (double)height;
    double fov_adjust = tan((cam.fov * M_PI / 180.0) / 2.0);

    double px = (2 * ((x + 0.5) / (double)width) - 1) * aspect_ratio * fov_adjust;
    double py = (1 - 2 * ((y + 0.5) / (double)height)) * fov_adjust;

    t_vec3 dir = vec3_normalize((t_vec3){px, py, -1});
    return (t_ray){cam.position, dir};
}

int	render(t_data *data)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color;

	color = 0;

	int increment = 50;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			mlx_put_pixel(data->img, i, j, color);
			color += increment;
			++j;
		}
		color += increment;
		++i;
	}

	return (OK);
}