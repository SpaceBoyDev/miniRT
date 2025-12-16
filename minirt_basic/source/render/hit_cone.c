/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:44:39 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:44:41 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

double	calc_base_t(t_ray *r, t_vec3 base_center, t_vec3 axis)
{
	double	denom;
	double	t;

	denom = vec3_dot(r->direction, axis);
	if (fabs(denom) < EPS)
		return (-1.0);
	t = vec3_dot(vec3_sub(base_center, r->origin), axis) / denom;
	return (t);
}

void	hit_cone_base(t_hit *best, t_ray *r, t_cone_params *cp)
{
	t_vec3	base_center;
	t_vec3	v_to_base;
	double	t;
	double	base_r_sq;
	t_hit	h;

	base_center = vec3_add(cp->cone->position,
			vec3_scale(cp->axis, cp->cone->height));
	t = calc_base_t(r, base_center, cp->axis);
	if (t <= EPS)
		return ;
	v_to_base = vec3_sub(vec3_add(r->origin,
				vec3_scale(r->direction, t)), base_center);
	base_r_sq = (cp->cone->diameter / 2.0) * (cp->cone->diameter / 2.0);
	if (vec3_dot(v_to_base, v_to_base) > base_r_sq)
		return ;
	h = make_cone_hit(t, vec3_add(r->origin, vec3_scale(r->direction, t)),
			vec3_scale(cp->axis, -1.0), cp);
	update_best(best, &h);
}

t_hit	hit_cone(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_cone_params	cp;
	t_hit			best;

	best.did_hit = false;
	cp.cone = &(geo->cone);
	cp.axis = vec3_normalize(cp.cone->axis);
	cp.obj = obj;
	hit_cone_surface(&best, r, &cp);
	hit_cone_base(&best, r, &cp);
	return (best);
}
