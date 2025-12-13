/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:44:55 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:44:56 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

static t_ray_quad	calc_discriminant(t_ray *r, t_sphere *s, t_vec3 offset)
{
	t_ray_quad	q;
	double		radius_sq;

	radius_sq = pow(s->diameter / 2.0, 2.0);
	q.a = vec3_dot(r->direction, r->direction);
	q.b = 2.0 * vec3_dot(offset, r->direction);
	q.c = vec3_dot(offset, offset) - radius_sq;
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

static void	fill_hit_sphere(t_ray *r, t_sphere *s, double dst, t_hit *hit)
{
	if (dst >= 0)
	{
		hit->did_hit = true;
		hit->distance = dst;
		hit->hit_point = vec3_add(r->origin, vec3_scale(r->direction, dst));
		hit->normal = vec3_normalize(vec3_sub(hit->hit_point, s->position));
		if (vec3_dot(hit->normal, r->direction) > 0)
			hit->normal = vec3_scale(hit->normal, -1.0);
		hit->color = s->color;
	}
}

t_hit	hit_sphere(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_sphere	*s;
	t_hit		hit;
	t_vec3		offset;
	t_ray_quad	q;
	double		dst;

	s = &(geo->sphere);
	clear_hit(&hit);
	hit.hit_obj = obj;
	offset = vec3_sub(r->origin, s->position);
	q = calc_discriminant(r, s, offset);
	if (q.discriminant >= 0)
	{
		dst = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
		fill_hit_sphere(r, s, dst, &hit);
	}
	return (hit);
}
