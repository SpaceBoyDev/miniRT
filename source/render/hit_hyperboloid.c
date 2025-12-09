#include "../../include/render.h"
#include "../../include/vector.h"

static t_hit	make_hyperboloid_hit(double t, t_vec3 p, t_vec3 n,
	t_hyperboloid *h, t_obj *obj)
{
	t_hit	hit;

	hit = (t_hit){0};

	hit.did_hit = true;
	hit.distance = t;
	hit.hit_point = p;
	hit.normal = n;
	hit.hit_obj = obj;
	hit.color = h->color;
	return (hit);
}

t_vec3	compute_hyper_normal(t_vec3 p, t_hyperboloid *h, t_vec3 axis)
{
	t_vec3	v_offset;
	t_vec3	v_parall;
	t_vec3	v_perp;
	t_vec3	normal_raw;
	double	dot_p_a;

	v_offset = vec3_sub(p, h->position);
	dot_p_a = vec3_dot(v_offset, axis);

	v_parall = vec3_scale(axis, dot_p_a);
	v_perp = vec3_sub(v_offset, v_parall);

	normal_raw = vec3_sub(
		vec3_scale(v_perp, 2.0 / (h->a_param * h->a_param)),
		vec3_scale(v_parall, 2.0 / (h->c_param * h->c_param))
	);

	return (vec3_normalize(normal_raw));
}

static void	get_hyper_abc(t_ray *r, t_hyperboloid *h, double *abc)
{
	t_vec3	oc;
	t_vec3	axis;
	double	d_dot_a;
	double	oc_dot_a;
	double	d_dot_d;
	double	oc_dot_oc;

	axis = h->axis;
	oc = vec3_sub(r->origin, h->position);

	d_dot_a = vec3_dot(r->direction, axis);
	oc_dot_a = vec3_dot(oc, axis);

	d_dot_d = vec3_dot(r->direction, r->direction);
	oc_dot_oc = vec3_dot(oc, oc);

	abc[0] = (d_dot_d - d_dot_a * d_dot_a) / (h->a_param * h->a_param);
	abc[0] -= (d_dot_a * d_dot_a) / (h->c_param * h->c_param);

	abc[1] = 2.0 * ((vec3_dot(r->direction, oc) - d_dot_a * oc_dot_a)
	/ (h->a_param * h->a_param));
	abc[1] -= 2.0 * ((d_dot_a * oc_dot_a) / (h->c_param * h->c_param));
	abc[2] = (oc_dot_oc - oc_dot_a * oc_dot_a) / (h->a_param * h->a_param);
	abc[2] -= (oc_dot_a * oc_dot_a) / (h->c_param * h->c_param);
	abc[2] -= 1.0;
}

static void	hit_hyperboloid_surface(t_hit *best, t_ray *r,
	t_hyperboloid *h, t_obj *obj)
{
	double	abc[3];
	double	disc;
	double	t[2];
	
	get_hyper_abc(r, h, &abc[0]);
	disc = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];

	if (disc < 0 || fabs(abc[0]) < EPS)
		return ;
	
	disc = sqrt(disc);
	t[0] = (-abc[1] - disc) / (2.0 * abc[0]);
	t[1] = (-abc[1] + disc) / (2.0 * abc[0]);

	for (int i = 0; i < 2; i++)
	{
		if (t[i] <= EPS)
			continue;

		t_vec3	p = vec3_add(r->origin, vec3_scale(r->direction, t[i]));
		double	h_proj = vec3_dot(vec3_sub(p, h->position), h->axis);
		
		if (fabs(h_proj) > h->h_limit / 2.0)
			continue;

		t_vec3	n = compute_hyper_normal(p, h, h->axis);

		if (vec3_dot(n, r->direction) > 0.0)
			n = vec3_scale(n, -1.0);
		t_hit	hit = make_hyperboloid_hit(t[i], p, n, h, obj);
		update_best(best, &hit);
	}
}


t_hit	hit_hyperboloid(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hyperboloid	*h;
	t_hit			best_hit;
	t_vec3			axis;

	best_hit = (t_hit){0};
	h = &(geo->hyperboloid);
	clear_hit(&best_hit);
	axis = vec3_normalize(h->axis);
	h->axis = axis;
	hit_hyperboloid_surface(&best_hit, r, h, obj);

	return (best_hit);
}
