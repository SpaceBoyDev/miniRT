/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_hyperboloid3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alepinto <alepinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:15:44 by alepinto          #+#    #+#             */
/*   Updated: 2025/12/14 06:15:45 by alepinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

double	calc_hyper_a(t_hyper_dots dots, t_hyperboloid *h)
{
	double	a;
	double	a_sq;
	double	c_sq;

	a_sq = h->a_param * h->a_param;
	c_sq = h->c_param * h->c_param;
	a = (dots.d_dot_d - dots.d_dot_a * dots.d_dot_a) / a_sq;
	a = a - (dots.d_dot_a * dots.d_dot_a) / c_sq;
	return (a);
}

double	calc_hyper_b(t_hyper_dots dots, t_hyperboloid *h)
{
	double	b;
	double	a_sq;
	double	c_sq;

	a_sq = h->a_param * h->a_param;
	c_sq = h->c_param * h->c_param;
	b = 2.0 * ((dots.d_dot_oc - dots.d_dot_a * dots.oc_dot_a) / a_sq);
	b = b - 2.0 * ((dots.d_dot_a * dots.oc_dot_a) / c_sq);
	return (b);
}

double	calc_hyper_c(t_hyper_dots dots, t_hyperboloid *h)
{
	double	c;
	double	a_sq;
	double	c_sq;

	a_sq = h->a_param * h->a_param;
	c_sq = h->c_param * h->c_param;
	c = (dots.oc_dot_oc - dots.oc_dot_a * dots.oc_dot_a) / a_sq;
	c = c - (dots.oc_dot_a * dots.oc_dot_a) / c_sq;
	c = c - 1.0;
	return (c);
}

t_quadratic	get_hyper_quadratic(t_ray *r, t_hyperboloid *h)
{
	t_vec3			oc;
	t_hyper_dots	dots;
	t_quadratic		q;

	oc = vec3_sub(r->origin, h->position);
	dots = init_hyper_dots(r, oc, h->axis);
	q.a = calc_hyper_a(dots, h);
	q.b = calc_hyper_b(dots, h);
	q.c = calc_hyper_c(dots, h);
	q.disc = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

bool	check_hyper_height(t_vec3 p, t_hyper_params *hp)
{
	double	h_proj;

	h_proj = vec3_dot(vec3_sub(p, hp->hyper->position), hp->axis);
	if (fabs(h_proj) > hp->hyper->h_limit / 2.0)
		return (false);
	return (true);
}
