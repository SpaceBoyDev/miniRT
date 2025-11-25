/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:17:20 by dario             #+#    #+#             */
/*   Updated: 2025/11/25 20:55:37 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

bool	light_is_behind(t_hit *hit, t_ray *ray)
{
	return (vec3_dot(hit->normal, ray->direction) < 0);
}

t_vec3	calc_dir(t_vec3 from, t_vec3 to)
{
	return (vec3_normalize(vec3_sub(to, from)));
}

bool	light_bounce(t_hit *hit, t_scene *scene)
{
	t_ray	ray;
	t_obj	*closest_obj;
	t_hit	light_hit;
	t_vec3	origin_adjusted;

	clear_hit(&light_hit);

	origin_adjusted = vec3_add(hit->hit_point, vec3_scale(hit->normal, EPS));

	ray.direction = calc_dir(origin_adjusted, scene->light->position);
	ray.origin = origin_adjusted;

	// printf("Dirección: %f, %f, %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	// printf("Origen: %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
	// printf("Origen original: %f, %f, %f\n", hit->hit_point.x, hit->hit_point.y, hit->hit_point.z);
	// exit(1);

	closest_obj = get_closest_obj(&ray, scene, &light_hit);

	if (!closest_obj && !light_is_behind(&light_hit, &ray))
	{
		return (true);
	}
	return (false);
}
