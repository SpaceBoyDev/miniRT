/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/26 20:50:38 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_ray	generate_ray(t_camera *cam, int x, int y, int width, int height)
{
	double aspect_ratio = (double)width / (double)height;
	double fov_adjust = tan((cam->fov * M_PI / 180.0) / 2.0);

	double px = (2 * ((x + 0.5) / (double)width) - 1) * aspect_ratio * fov_adjust;
	double py = (1 - 2 * ((y + 0.5) / (double)height)) * fov_adjust;

	t_vec3 dir = vec3_normalize((t_vec3){-px, -py, -1});
	return (t_ray){cam->position, dir};
}

bool	hit_sphere(t_sphere *s, t_ray *r, double *t)
{
	t_vec3 oc = vec3_add(r->origin, s->position);
	double a = vec3_dot(r->direction, r->direction);
	double b = 2.0 * vec3_dot(oc, r->direction);
	double c = vec3_dot(oc, oc) - (s->diameter/2) * (s->diameter/2);
	double discriminant = b*b - 4*a*c;

	if (discriminant < 0)
		return false;
	else
	{
		double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
		double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
		*t = (t0 < t1) ? t0 : t1;
		return true;
	}
}

t_color	trace_ray(t_ray *ray, t_scene *scene)
{
	double t_min = INFINITY;
	t_sphere	*current;
	t_sphere *hit = NULL;

	current = scene->sphere_list;
	while (current)
	{
		double t;
		if (hit_sphere(current, ray, &t) && t < t_min && t > 0)
		{
			t_min = t;
			hit = current;
		}
		current = current->next;
	}

	if (hit)
		return (hit->color);
	else
		return ((t_color){0, 0, 0});
}

uint32_t	rgb_to_uint(t_color *color)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | 255);
}

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
