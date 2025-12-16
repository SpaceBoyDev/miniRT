/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_hyperboloid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:44:46 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:44:47 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

static t_vec3	adjust_normal(t_vec3 n, t_ray *r)
{
	t_vec3	adjusted;

	adjusted = n;
	if (vec3_dot(n, r->direction) > 0.0)
		adjusted = vec3_scale(n, -1.0);
	return (adjusted);
}

static void	try_hyper_t(t_hit *best, double t, t_ray *r, t_hyper_params *hp)
{
	t_vec3	p;
	t_vec3	n;
	t_hit	hit;

	if (t <= EPS)
		return ;
	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	if (!check_hyper_height(p, hp))
		return ;
	n = compute_hyper_normal(p, hp->hyper, hp->axis);
	n = adjust_normal(n, r);
	hit = make_hyperboloid_hit(t, p, n, hp);
	update_best(best, &hit);
}

static void	solve_hyper_hits(t_hit *best, t_ray *r, t_hyper_params *hp,
		t_quadratic q)
{
	double	t0;
	double	t1;
	int		i;

	t0 = (-q.b - sqrt(q.disc)) / (2.0 * q.a);
	t1 = (-q.b + sqrt(q.disc)) / (2.0 * q.a);
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			try_hyper_t(best, t0, r, hp);
		else
			try_hyper_t(best, t1, r, hp);
		i++;
	}
}

static void	hit_hyperboloid_surface(t_hit *best, t_ray *r, t_hyper_params *hp)
{
	t_quadratic	q;

	q = get_hyper_quadratic(r, hp->hyper);
	if (q.disc < 0 || fabs(q.a) < EPS)
		return ;
	solve_hyper_hits(best, r, hp, q);
}

t_hit	hit_hyperboloid(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hyper_params	hp;
	t_hit			best_hit;

	best_hit.did_hit = false;
	hp.hyper = &(geo->hyperboloid);
	hp.axis = vec3_normalize(hp.hyper->axis);
	hp.obj = obj;
	hp.hyper->axis = hp.axis;
	hit_hyperboloid_surface(&best_hit, r, &hp);
	return (best_hit);
}
