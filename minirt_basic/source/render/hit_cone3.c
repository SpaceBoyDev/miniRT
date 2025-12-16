/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alepinto <alepinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 06:15:26 by alepinto          #+#    #+#             */
/*   Updated: 2025/12/14 06:15:27 by alepinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

double	calc_cone_k(t_cone *c)
{
	double	k;
	double	radius;

	radius = c->diameter / 2.0;
	k = (c->height * c->height) / (radius * radius + c->height * c->height);
	return (k);
}

bool	check_cone_height(t_vec3 p, t_cone_params *cp)
{
	double	h;

	h = vec3_dot(vec3_sub(p, cp->cone->position), cp->axis);
	if (h < 0 || h > cp->cone->height)
		return (false);
	return (true);
}

void	try_cone_t(t_hit *best, double t, t_ray *r, t_cone_params *cp)
{
	t_vec3	p;
	t_hit	hit;

	if (t <= EPS)
		return ;
	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	if (!check_cone_height(p, cp))
		return ;
	hit = make_cone_hit(t, p, compute_cone_normal(p, cp,
				cp->cone->diameter / 2.0), cp);
	update_best(best, &hit);
}

void	solve_cone_hits(t_hit *best, t_ray *r, t_cone_params *cp,
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
			try_cone_t(best, t0, r, cp);
		else
			try_cone_t(best, t1, r, cp);
		i++;
	}
}

void	hit_cone_surface(t_hit *best, t_ray *r, t_cone_params *cp)
{
	double		k;
	t_vec3		oc;
	t_cone_calc	calc;
	t_quadratic	q;

	oc = vec3_sub(r->origin, cp->cone->position);
	k = calc_cone_k(cp->cone);
	calc = init_cone_calc(r, oc, cp->axis);
	q = get_cone_quadratic(k, calc, oc);
	if (q.disc < 0)
		return ;
	solve_cone_hits(best, r, cp, q);
}
