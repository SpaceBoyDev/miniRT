/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:04:15 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 17:37:25 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_sphere	*check_spheres(t_ray *ray, t_hit *ray_hit, t_scene *scene)
{
	double		t_min;
	t_sphere	*current;
	t_sphere	*hit;

	t_min = INFINITY;
	hit = NULL;
	current = scene->sphere_list;
	while (current)
	{
		*ray_hit = hit_sphere(current, ray);
		if (ray_hit->did_hit && ray_hit->distance < t_min)
		{
			t_min = ray_hit->distance;
			hit = current;
		}
		current = current->next;
	}
	return (hit);
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
			hit.hit_color = s->color;
		}
	}
	return (hit);
}
