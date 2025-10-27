/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:42:28 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 18:16:04 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	hit_plane(t_plane *p, t_ray *r)
{
	t_hit	hit;
	double	denominator = vec3_dot(r->direction, p->normal);

	if (abs(denominator) < __DBL_EPSILON__)
		return (hit);
	double	dst = vec3_dot(vec3_sub(p->position, r->origin), p->normal) / denominator;
	if (dst < 0)
		return (hit);
	hit.did_hit = true;
	hit.distance = dst;
	//hit.hit_point =
	hit.normal = p->normal;
	return (hit);
}

t_sphere	*check_planes(t_ray *ray, t_hit *ray_hit, t_scene *scene)
{
	double		t_min;
	t_plane		*current;
	t_plane		*hit;

	t_min = INFINITY;
	hit = NULL;
	current = scene->plane_list;
	while (current)
	{
		*ray_hit = hit_plane(current, ray);
		if (ray_hit->did_hit && ray_hit->distance < t_min)
		{
			t_min = ray_hit->distance;
			hit = current;
		}
		current = current->next;
	}
	return (hit);
}
