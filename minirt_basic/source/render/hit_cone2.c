/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alepinto <alepinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:13:45 by alepinto          #+#    #+#             */
/*   Updated: 2025/12/14 06:13:46 by alepinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	make_cone_hit(double t, t_vec3 p, t_vec3 n, t_cone_params *cp)
{
	t_hit	h;

	h.did_hit = true;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = cp->obj;
	h.color = cp->cone->color;
	return (h);
}

t_vec3	calc_radial(t_vec3 p, t_vec3 apex, t_vec3 axis, double h)
{
	t_vec3	radial;

	radial = vec3_sub(p, vec3_add(apex, vec3_scale(axis, h)));
	return (radial);
}

t_vec3	compute_cone_normal(t_vec3 p, t_cone_params *cp, double base_r)
{
	t_vec3	v_apex_to_p;
	t_vec3	radial;
	double	h;
	double	k;

	v_apex_to_p = vec3_sub(p, cp->cone->position);
	h = vec3_dot(v_apex_to_p, cp->axis);
	if (h < EPS)
		h = EPS;
	k = base_r / cp->cone->height;
	radial = calc_radial(p, cp->cone->position, cp->axis, h);
	return (vec3_normalize(vec3_sub(radial,
				vec3_scale(cp->axis, k * vec3_magnitude(radial)))));
}

t_cone_calc	init_cone_calc(t_ray *r, t_vec3 oc, t_vec3 axis)
{
	t_cone_calc	calc;

	calc.d_dot_a = vec3_dot(r->direction, axis);
	calc.oc_dot_a = vec3_dot(oc, axis);
	calc.d_dot_oc = vec3_dot(r->direction, oc);
	calc.d_dot_d = vec3_dot(r->direction, r->direction);
	return (calc);
}

t_quadratic	get_cone_quadratic(double k, t_cone_calc calc, t_vec3 oc)
{
	t_quadratic	q;

	q.a = (calc.d_dot_a * calc.d_dot_a) - (calc.d_dot_d * k);
	q.b = 2.0 * ((calc.d_dot_a * calc.oc_dot_a) - (calc.d_dot_oc * k));
	q.c = (calc.oc_dot_a * calc.oc_dot_a) - (vec3_dot(oc, oc) * k);
	q.disc = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}
