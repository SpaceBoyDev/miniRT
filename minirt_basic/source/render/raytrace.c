/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darmarti <darmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:03 by dario             #+#    #+#             */
/*   Updated: 2025/12/16 11:52:15 by darmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

static t_hit	dispatch_hit_func(t_obj *obj, t_ray *ray)
{
	if (obj->id == 0)
		return (hit_sphere(obj, obj->geo, ray));
	else if (obj->id == 1)
		return (hit_plane(obj, obj->geo, ray));
	else if (obj->id == 2)
		return (hit_cylinder(obj, obj->geo, ray));
	else if (obj->id == 3)
		return (hit_cone(obj, obj->geo, ray));
	return ((t_hit){0});
}

t_obj	*get_closest_obj(t_ray *ray, t_scene *scene, t_hit *out_hit)
{
	t_obj		*closest;
	t_obj		*obj;
	t_hit		hit;
	double		closest_dist;

	closest = NULL;
	closest_dist = INFINITY;
	if (!scene || !scene->objs)
		return (NULL);
	obj = scene->objs;
	while (obj)
	{
		hit = dispatch_hit_func(obj, ray);
		if (hit.did_hit)
		{
			if (hit.distance > 0 && hit.distance < closest_dist)
			{
				closest_dist = hit.distance;
				closest = obj;
				*out_hit = hit;
			}
		}
		obj = obj->next;
	}
	return (closest);
}

t_color	trace_ray(t_ray *ray, t_scene *scene)
{
	t_hit	hit;
	t_obj	*closest_obj;

	clear_hit(&hit);
	closest_obj = get_closest_obj(ray, scene, &hit);
	if (closest_obj)
		return (light_bounce(&hit, scene));
	else
		return ((t_color){0, 0, 0});
}
