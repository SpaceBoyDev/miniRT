/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:03 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 17:42:23 by dario            ###   ########.fr       */
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

	t_vec3 forward = vec3_normalize(cam->orientation);
	t_vec3 world_up = (fabs(forward.y) > 0.999) ? (t_vec3){0, 0, 1} : (t_vec3){0, 1, 0};
	t_vec3 right = vec3_normalize(vec3_cross(forward, world_up));
	t_vec3 up = vec3_cross(right, forward);

	t_vec3 cam_dir = (t_vec3){-px, -py, -1.0};
	t_vec3 dir = vec3_normalize(
		vec3_add(
			vec3_add(vec3_scale(right, cam_dir.x), vec3_scale(up, cam_dir.y)),
			vec3_scale(forward, cam_dir.z)
		)
	);

	return (t_ray){cam->position, dir};
}

t_hit	bounce_ray(t_hit last_hit, t_scene *scene)
{
	double		t_min;
	t_sphere	*current;
	t_sphere	*hit;
	t_hit		ray_hit;
	t_ray		ray;

	ray.origin = last_hit.hit_point;
	ray.direction = vec3_sub(scene->light->position, last_hit.hit_point);
	(void)hit;
	t_min = INFINITY;
	hit = NULL;
	current = scene->sphere_list;
	while (current)
	{
		ray_hit = hit_sphere(current, &ray);
		if (ray_hit.did_hit && ray_hit.distance < t_min)
		{
			t_min = ray_hit.distance;
			hit = current;
		}
		current = current->next;
	}
	return (ray_hit);
}

t_color	trace_ray(t_ray *ray, t_scene *scene)
{
	double		t_min;
	t_sphere	*current;
	t_sphere	*hit;
	t_hit		ray_hit;

	t_min = INFINITY;
	hit = NULL;
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
