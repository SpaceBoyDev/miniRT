/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 13:34:59 by dario            ###   ########.fr       */
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

	/* camera basis from cam->orientation */
	t_vec3 forward = vec3_normalize(cam->orientation);
	t_vec3 world_up = (fabs(forward.y) > 0.999) ? (t_vec3){0, 0, 1} : (t_vec3){0, 1, 0};
	t_vec3 right = vec3_normalize(vec3_cross(forward, world_up));
	t_vec3 up = vec3_cross(right, forward);

	/* camera-space direction (matches previous convention: -px, -py, -1) */
	t_vec3 cam_dir = (t_vec3){-px, -py, -1.0};
	t_vec3 dir = vec3_normalize(
		vec3_add(
			vec3_add(vec3_scale(right, cam_dir.x), vec3_scale(up, cam_dir.y)),
			vec3_scale(forward, cam_dir.z)
		)
	);

	return (t_ray){cam->position, dir};
}

t_hit	hit_sphere(t_sphere *s, t_ray *r)
{
	t_hit	hit;
	t_vec3	offset;
	double	a;
	double	b; 
	double	c;
	double	discriminant;
	double	dst;

	offset = vec3_add(r->origin, s->position);
	a = vec3_dot(r->direction, r->direction);
	b = 2 * vec3_dot(offset, r->direction);
	c = vec3_dot(offset, offset) - pow(s->diameter/2, 2);
	discriminant = b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		dst = (-b - sqrt(discriminant)) / (2.0 * a);
		if (dst >= 0)
		{
			hit.did_hit = true;
			hit.distance = dst;
			hit.hit_point = vec3_scale(vec3_add(r->origin, r->direction), dst);
			hit.normal = vec3_normalize(vec3_sub(hit.hit_point, s->position));
		}
	}
	return (hit);
}

t_color	trace_ray(t_ray *ray, t_scene *scene)
{
	double t_min = INFINITY;
	t_sphere	*current;
	t_sphere *hit = NULL;
	t_hit	ray_hit;

	current = scene->sphere_list;
	while (current)
	{
		ray_hit = hit_sphere(current, ray);
		if (ray_hit.did_hit && ray_hit.distance < t_min)
		{
			t_min = ray_hit.distance;
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
