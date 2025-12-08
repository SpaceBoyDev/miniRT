/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:17:20 by dario             #+#    #+#             */
/*   Updated: 2025/12/08 23:55:55 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

static t_vec3	calc_dir(t_vec3 from, t_vec3 to, bool normalize)
{
	if (normalize)
		return (vec3_normalize(vec3_sub(to, from)));
	else
		return (vec3_sub(to, from));
}

static void	clamp_values(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
}

static void	apply_lambert(t_light *light, t_hit point, t_color *final)
{
	double	attenuation;
	double	lambert;
	double	intensity;
	t_vec3	light_dir;

	light_dir = calc_dir(point.hit_point, light->position, true);
	lambert = vec3_dot(point.normal, light_dir);
	if (lambert < 0)
		lambert = 0;
	attenuation = 1.0 / (1.0 + 0.1 * point.distance);
	intensity = light->brightness * attenuation * lambert;
	final->r += point.color.r * light->color.r * intensity;
	final->g += point.color.g * light->color.g * intensity;
	final->b += point.color.b * light->color.b * intensity;
}

static void	apply_ambient(t_ambient *ambient, t_color *color)
{
	color->r *= ambient->color.r * ambient->lighting;
	color->g *= ambient->color.g * ambient->lighting;
	color->b *= ambient->color.b * ambient->lighting;
}

t_color	light_bounce(t_hit *hit, t_scene *scene)
{
	t_ray	ray;
	t_obj	*closest_obj;
	t_hit	light_hit;
	t_vec3	origin_adjusted;
	t_color	final;

	clear_hit(&light_hit);
	final = hit->color;
	hit->distance = vec3_magnitude(calc_dir
			(hit->hit_point, scene->light->position, false));
	origin_adjusted = vec3_add(hit->hit_point, vec3_scale(hit->normal, EPS));
	ray.direction = calc_dir(origin_adjusted, scene->light->position, true);
	ray.origin = origin_adjusted;
	closest_obj = get_closest_obj(&ray, scene, &light_hit);
	apply_ambient(scene->ambient, &final);
	if (!closest_obj || (closest_obj && hit->distance < light_hit.distance))
		apply_lambert(scene->light, *hit, &final);
	clamp_values(&final);
	return (final);
}
