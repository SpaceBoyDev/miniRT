/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_paraboloid2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:44:51 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:44:52 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	make_paraboloid_hit(t_pb_ctx *ctx, double t,
					t_vec3 p, t_vec3 n)
{
	t_hit	h;

	h = (t_hit){0};
	h.did_hit = 1;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = ctx->obj;
	h.color = ctx->pb->color;
	return (h);
}

static t_vec3	compute_paraboloid_normal(t_vec3 p, t_pb_ctx *ctx)
{
	t_vec3	v;
	t_vec3	radial_proj;
	t_vec3	n;
	double	h;

	v = vec3_sub(p, ctx->pb->position);
	h = vec3_dot(v, ctx->axis);
	radial_proj = vec3_sub(v, vec3_scale(ctx->axis, h));
	n = vec3_sub(vec3_scale(radial_proj, 2.0),
			vec3_scale(ctx->axis, ctx->pb->k_factor));
	return (vec3_normalize(n));
}

static void	check_intersection(t_hit *best, t_pb_ctx *ctx, double t)
{
	t_vec3	p;
	t_vec3	n;
	double	h;
	t_hit	hit;

	if (t <= EPS)
		return ;
	p = vec3_add(ctx->r->origin, vec3_scale(ctx->r->direction, t));
	h = vec3_dot(vec3_sub(p, ctx->pb->position), ctx->axis);
	if (h < 0.0 || h > ctx->pb->h_limit)
		return ;
	n = compute_paraboloid_normal(p, ctx);
	if (vec3_dot(n, ctx->r->direction) > 0)
		n = vec3_scale(n, -1.0);
	hit = make_paraboloid_hit(ctx, t, p, n);
	if (hit.did_hit && (!best->did_hit || hit.distance < best->distance))
		*best = hit;
}

void	solve_quadratic(t_hit *best, t_pb_ctx *ctx, t_quad *q)
{
	double	t[2];
	double	temp;
	int		i;

	q->disc = q->b * q->b - 4.0 * q->a * q->c;
	if (q->disc < 0)
		return ;
	q->disc = sqrt(q->disc);
	if (q->b < 0)
		q->disc = -0.5 * (q->b - q->disc);
	else
		q->disc = -0.5 * (q->b + q->disc);
	t[0] = q->disc / q->a;
	t[1] = q->c / q->disc;
	if (t[0] > t[1])
	{
		temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}
	i = -1;
	while (++i < 2)
		check_intersection(best, ctx, t[i]);
}

t_quad	init_quadratic_pa(t_pb_ctx *ctx)
{
	t_vec3	v;
	double	d_dot_a;
	double	v_dot_a;
	t_quad	q;

	v = vec3_sub(ctx->r->origin, ctx->pb->position);
	d_dot_a = vec3_dot(ctx->r->direction, ctx->axis);
	v_dot_a = vec3_dot(v, ctx->axis);
	q.a = vec3_dot(ctx->r->direction, ctx->r->direction) - pow(d_dot_a, 2);
	q.b = 2.0 * (vec3_dot(v, ctx->r->direction) - v_dot_a * d_dot_a)
		- ctx->pb->k_factor * d_dot_a;
	q.c = vec3_dot(v, v) - pow(v_dot_a, 2) - ctx->pb->k_factor * v_dot_a;
	q.disc = 0;
	return (q);
}
