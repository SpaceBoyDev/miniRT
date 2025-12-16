/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_hyperboid2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alepinto <alepinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:15:37 by alepinto          #+#    #+#             */
/*   Updated: 2025/12/14 06:24:39 by alepinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	make_hyperboloid_hit(double t, t_vec3 p, t_vec3 n,
		t_hyper_params *hp)
{
	t_hit	hit;

	hit.did_hit = true;
	hit.distance = t;
	hit.hit_point = p;
	hit.normal = n;
	hit.hit_obj = hp->obj;
	hit.color = hp->hyper->color;
	return (hit);
}

t_hyper_vecs	calc_hyper_vecs(t_vec3 p, t_hyperboloid *h, t_vec3 axis)
{
	t_hyper_vecs	vecs;
	double			dot_p_a;

	vecs.v_offset = vec3_sub(p, h->position);
	dot_p_a = vec3_dot(vecs.v_offset, axis);
	vecs.v_parall = vec3_scale(axis, dot_p_a);
	vecs.v_perp = vec3_sub(vecs.v_offset, vecs.v_parall);
	return (vecs);
}

t_vec3	calc_normal_raw(t_hyper_vecs vecs, t_hyperboloid *h)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	normal_raw;

	term1 = vec3_scale(vecs.v_perp, 2.0 / (h->a_param * h->a_param));
	term2 = vec3_scale(vecs.v_parall, 2.0 / (h->c_param * h->c_param));
	normal_raw = vec3_sub(term1, term2);
	return (normal_raw);
}

t_vec3	compute_hyper_normal(t_vec3 p, t_hyperboloid *h, t_vec3 axis)
{
	t_hyper_vecs	vecs;
	t_vec3			normal_raw;

	vecs = calc_hyper_vecs(p, h, axis);
	normal_raw = calc_normal_raw(vecs, h);
	return (vec3_normalize(normal_raw));
}

t_hyper_dots	init_hyper_dots(t_ray *r, t_vec3 oc, t_vec3 axis)
{
	t_hyper_dots	dots;

	dots.d_dot_a = vec3_dot(r->direction, axis);
	dots.oc_dot_a = vec3_dot(oc, axis);
	dots.d_dot_d = vec3_dot(r->direction, r->direction);
	dots.oc_dot_oc = vec3_dot(oc, oc);
	dots.d_dot_oc = vec3_dot(r->direction, oc);
	return (dots);
}
