/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:03 by dario             #+#    #+#             */
/*   Updated: 2025/11/26 16:15:20 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_ray	generate_ray(t_camera *cam, int x, int y)
{
	double aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	double fov_adjust = tan((cam->fov * M_PI / 180.0) / 2.0);

	double px = (2 * ((x + 0.5) / (double)WIN_WIDTH) - 1) * aspect_ratio * fov_adjust;
	double py = (1 - 2 * ((y + 0.5) / (double)WIN_HEIGHT)) * fov_adjust;

	t_vec3 forward = vec3_normalize(cam->orientation);
	t_vec3 world_up = (fabs(forward.y) > 0.999) ? (t_vec3){0, 0, 1} : (t_vec3){0, 1, 0};
	t_vec3 right = vec3_normalize(vec3_cross(forward, world_up));
	t_vec3 up = vec3_cross(right, forward);

	t_vec3 cam_dir = (t_vec3){px, py, 1.0};
	t_vec3 dir = vec3_normalize(vec3_add(vec3_add(vec3_scale(right, cam_dir.x),
			vec3_scale(up, cam_dir.y)),
			vec3_scale(forward, cam_dir.z)));

	return (t_ray){cam->position, dir};
}

t_obj	*get_closest_obj(t_ray *ray, t_scene *scene, t_hit *out_hit)
{
	t_obj	*closest = NULL;
	t_obj	*obj;
	t_hit	hit;
	double	closest_dist = INFINITY;
    t_hit (*hit_funcs[3])(t_obj*, t_geo*, t_ray*) = {hit_sphere, hit_plane, hit_cylinder};

	if (!scene || !scene->objs)
		return (NULL);
	obj = scene->objs;
	while (obj)
	{
        hit = hit_funcs[obj->id](obj, obj->geo, ray);
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
		return ((t_color){0,0,0});
}
