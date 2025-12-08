/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:43:01 by dario             #+#    #+#             */
/*   Updated: 2025/12/08 23:54:31 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

typedef struct s_quad
{
	double a;
	double b;
	double c;
	double disc;
} t_quad;

typedef struct s_cyl_data
{
	t_cylinder *cyl;
	t_vec3 axis;
	double radius;
	t_obj *obj;
} t_cyl_data;

static void init_quad(t_quad *q, t_vec3 d_perp, t_vec3 oc_perp, double r)
{
	q->a = vec3_dot(d_perp, d_perp);
	q->b = 2 * vec3_dot(oc_perp, d_perp);
	q->c = vec3_dot(oc_perp, oc_perp) - r * r;
	q->disc = q->b * q->b - 4 * q->a * q->c;
}

static t_hit make_hit(double t, t_vec3 p, t_vec3 n, t_cyl_data *data)
{
	t_hit h = {0};
	h.did_hit = true;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = data->obj;
	h.color = data->cyl->color;
	return h;
}

static t_hit check_lateral_hit(t_ray *r, double t, 
								double height, t_cyl_data *data)
{
	t_hit h = {0};
	t_vec3 p;
	t_vec3 radial;
	
	if (height < 0 || height > data->cyl->height || t <= 0)
		return h;
	
	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	radial = vec3_sub(vec3_sub(p, data->cyl->position), vec3_scale(data->axis, height));
	return make_hit(t, p, vec3_normalize(radial), data);
}

static void hit_lateral(t_hit *best, t_ray *r, t_cyl_data *data)
{
	t_vec3 oc = vec3_sub(r->origin, data->cyl->position);
	double d_dot_a = vec3_dot(r->direction, data->axis);
	double oc_dot_a = vec3_dot(oc, data->axis);
	t_vec3 d_perp = vec3_sub(r->direction, vec3_scale(data->axis, d_dot_a));
	t_vec3 oc_perp = vec3_sub(oc, vec3_scale(data->axis, oc_dot_a));
	
	t_quad q;
	init_quad(&q, d_perp, oc_perp, data->radius);
	
	if (fabs(q.a) < 1e-9 || q.disc < 0)
		return;
	
	double sqrtD = sqrt(q.disc);
	double t[2] = {(-q.b - sqrtD) / (2 * q.a), (-q.b + sqrtD) / (2 * q.a)};
	
	for (int i = 0; i < 2; i++)
	{
		t_vec3 p = vec3_add(r->origin, vec3_scale(r->direction, t[i]));
		double h = vec3_dot(vec3_sub(p, data->cyl->position), data->axis);
		t_hit hit = check_lateral_hit(r, t[i], h, data);
		update_best(best, &hit);
	}
}

static void hit_cap(t_hit *best, t_ray *r, 
					t_vec3 center, t_vec3 normal, t_cyl_data *data)
{
	double denom = vec3_dot(r->direction, data->axis);
	double t;
	t_vec3 p;
	double dist2;
	
	if (fabs(denom) < 1e-9)
		return;
	
	t = vec3_dot(vec3_sub(center, r->origin), data->axis) / denom;
	if (t <= 0)
		return;
	
	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	dist2 = vec3_dot(vec3_sub(p, center), vec3_sub(p, center));
	
	if (dist2 <= data->radius * data->radius)
	{
		t_hit h = make_hit(t, p, normal, data);
		update_best(best, &h);
	}
}

t_hit hit_cylinder(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_cyl_data data;
	t_hit best = {0};
	t_vec3 top_center;
	
	data.cyl = &(geo->cylinder);
	data.axis = vec3_normalize(data.cyl->axis);
	data.radius = data.cyl->diameter * 0.5;
	data.obj = obj;
	
	hit_lateral(&best, r, &data);
	hit_cap(&best, r, data.cyl->position, vec3_scale(data.axis, -1), &data);
	
	top_center = vec3_add(data.cyl->position, vec3_scale(data.axis, data.cyl->height));
	hit_cap(&best, r, top_center, data.axis, &data);
	
	return best;
}
