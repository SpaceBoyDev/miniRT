/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:43:08 by dario             #+#    #+#             */
/*   Updated: 2025/12/08 23:51:07 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	hit_plane(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hit	hit;
	t_plane	*p;
	double	denominator;
	double	dst;

	(void)obj;
	clear_hit(&hit);
	p = &(geo->plane);
	denominator = vec3_dot(r->direction, p->normal);
	if (fabs(denominator) < __DBL_EPSILON__)
		return (hit);
	dst = vec3_dot(vec3_sub(p->position, r->origin), p->normal) / denominator;
	if (dst < 0)
		return (hit);
	hit.did_hit = true;
	hit.distance = dst;
	hit.hit_point = vec3_add(r->origin, vec3_scale(r->direction, dst));
	if (vec3_dot(r->direction, p->normal) < 0)
		hit.normal = p->normal;
	else
		hit.normal = vec3_scale(p->normal, -1);
	hit.color = p->color;
	return (hit);
}
