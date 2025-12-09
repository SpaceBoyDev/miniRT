#include "../../include/render.h"
#include "../../include/vector.h"

static t_hit	make_cone_hit(double t, t_vec3 p, t_vec3 n, t_cone *c, t_obj *obj)
{
	t_hit	h;

	h.did_hit = true;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = obj;
	h.color = c->color;
	return (h);
}

static t_vec3	compute_cone_normal(t_vec3 p, t_cone *c, t_vec3 axis, double base_r)
{
	t_vec3	v_apex_to_p;
	t_vec3	radial;
	double	h;
	double	k;

	v_apex_to_p = vec3_sub(p, c->position);
	h = vec3_dot(v_apex_to_p, axis);
	if (h < EPS)
		h = EPS;
	k = base_r / c->height;

	radial = vec3_sub(p, vec3_add(c->position, vec3_scale(axis, h)));

	return (vec3_normalize(vec3_sub(radial,
		vec3_scale(axis, k * vec3_magnitude(radial)))));
}

static void	get_cone_abc(double k, t_ray *r, t_vec3 oc, t_vec3 axis, double *abc)
{
	double	d_dot_a;
	double	oc_dot_a;
	double	d_dot_oc;
	double	d_dot_d;

	d_dot_a = vec3_dot(r->direction, axis);
	oc_dot_a = vec3_dot(oc, axis);
	d_dot_oc = vec3_dot(r->direction, oc);
	d_dot_d = vec3_dot(r->direction, r->direction);

	abc[0] = (d_dot_a * d_dot_a) - (d_dot_d * k);
	abc[1] = 2.0 * ((d_dot_a * oc_dot_a) - (d_dot_oc * k));
	abc[2] = (oc_dot_a * oc_dot_a) - (vec3_dot(oc, oc) * k);
}

static void	hit_cone_surface(t_hit *best, t_ray *r, t_cone *c, t_vec3 axis, t_obj *obj)
{
	double	k;
	double	abc[3];
	t_vec3	oc;
	double	disc;
	double	t[2];

	oc = vec3_sub(r->origin, c->position);
	k = (c->height * c->height) / (pow(c->diameter / 2.0, 2) \
	+ c->height * c->height);
	get_cone_abc(k, r, oc, axis, abc);

	disc = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];

	if (disc < 0)
		return ;

	disc = sqrt(disc);
	t[0] = (-abc[1] - disc) / (2.0 * abc[0]);
	t[1] = (-abc[1] + disc) / (2.0 * abc[0]);

	for (int i = 0; i < 2; i++)
	{
		if (t[i] <= EPS) 
			continue;
		
		t_vec3	p = vec3_add(r->origin, vec3_scale(r->direction, t[i]));
		double	h = vec3_dot(vec3_sub(p, c->position), axis);
		
		if (h < 0 || h > c->height)
			continue;
		
		t_hit	hit = make_cone_hit(t[i], p, 
			compute_cone_normal(p, c, axis, c->diameter / 2.0), c, obj);
		update_best(best, &hit);
	}
}

static void	hit_cone_base(t_hit *best, t_ray *r, t_cone *c, t_vec3 axis, t_obj *obj)
{
	t_vec3	base_center;
	t_vec3	v_to_base;
	double	denom;
	double	t;

	base_center = vec3_add(c->position, vec3_scale(axis, c->height));
	denom = vec3_dot(r->direction, axis);
	if (fabs(denom) < EPS)
		return ;
	t = vec3_dot(vec3_sub(base_center, r->origin), axis) / denom;
	if (t <= EPS)
		return ;
	v_to_base = vec3_sub(vec3_add(r->origin, vec3_scale(r->direction, t)),
		base_center);
	double base_r_sq = pow(c->diameter / 2.0, 2);
	if (vec3_dot(v_to_base, v_to_base) <= base_r_sq)
	{
		t_hit	h = make_cone_hit(t, 
			vec3_add(r->origin, vec3_scale(r->direction, t)),
			vec3_scale(axis, -1.0), c, obj);
		update_best(best, &h);
	}
}

t_hit	hit_cone(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_cone	*c = &(geo->cone);
	t_vec3	axis;
	t_hit	best = {0};

	axis = vec3_normalize(c->axis);
	hit_cone_surface(&best, r, c, axis, obj);
	hit_cone_base(&best, r, c, axis, obj);
	return (best);
}
