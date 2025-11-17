/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:42:28 by dario             #+#    #+#             */
/*   Updated: 2025/11/13 18:52:44 by dario            ###   ########.fr       */
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
