/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:17:20 by dario             #+#    #+#             */
/*   Updated: 2025/11/17 20:19:42 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

bool	light_is_behind(t_hit *hit, t_ray *ray)
{
	return (vec3_dot(hit->normal, ray->direction) < 0);
}

t_vec3	calc_direction(t_vec3 start, t_vec3 end)
{
	return (vec3_normalize(vec3_sub(end, start)));
}

bool	light_bounce(t_hit *hit, t_scene *scene)
{
	t_ray	ray;
	t_obj	*closest_obj;
	t_hit	light_hit;

	clear_hit(&light_hit);

	ray.direction = calc_direction(hit->hit_point, scene->light->position);
	ray.origin = vec3_add(hit->hit_point, vec3_scale(hit->normal, EPS));

	closest_obj = get_closest_obj(&ray, scene, &light_hit);

	if (!closest_obj && !light_is_behind(&light_hit, &ray))
	{
		return (true);
	}
	return (false);
}
