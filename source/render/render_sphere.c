/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:04:15 by dario             #+#    #+#             */
/*   Updated: 2025/10/28 20:58:54 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	hit_sphere(t_obj *obj, t_sphere *s, t_ray *r)
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
	c = vec3_dot(offset, offset) - pow(s->diameter / 2, 2);
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
			hit.hit_obj = obj;
			hit.color = s->color;
		}
	}
	return (hit);
}
