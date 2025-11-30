/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:17:20 by dario             #+#    #+#             */
/*   Updated: 2025/11/26 16:44:47 by dario            ###   ########.fr       */
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

static void	apply_lambert(t_light *light, t_hit point, t_color color, t_color *final)
{
	double	attenuation;
	double	lambert;
	double	intensity;

    // hay que tomar la distancia al foco de luz , no a la camara.
	attenuation = 1.0 / (1.0 + 0.1 * point.distance);
	lambert = vec3_dot(point.normal, calc_dir(point.hit_point, light->position, true));
	if (lambert < 0)
		lambert = 0;
	intensity = light->brightness * attenuation * lambert;
	final->r += color.r * intensity; // (light->color.r * intensity); // TODO: Revisar cálculo de luz y que sea correcto
	final->g += color.g * intensity; // (light->color.g * intensity); // TODO: Revisar cálculo de luz y que sea correcto
	final->b += color.b * intensity; // (light->color.b * intensity); // TODO: Revisar cálculo de luz y que sea correcto
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
	hit->distance = vec3_magnitude(calc_dir(hit->hit_point, scene->light->position, false));
	origin_adjusted = vec3_add(hit->hit_point, vec3_scale(hit->normal, EPS));
	ray.direction = calc_dir(origin_adjusted, scene->light->position, true);
	ray.origin = origin_adjusted;
	closest_obj = get_closest_obj(&ray, scene, &light_hit);
	apply_ambient(scene->ambient, &final);
	if (!closest_obj || (closest_obj && hit->distance < light_hit.distance))
		apply_lambert(scene->light, *hit, hit->color, &final);
	clamp_values(&final);
	return (final);
}
