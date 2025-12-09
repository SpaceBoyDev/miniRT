#include "../../include/render.h"
#include "../../include/vector.h"

static void	process_lateral_roots(t_hit *best, t_ray *r,
				t_cyl_data *data, t_quad *q)
{
	double	sqrt_d;
	double	t[2];

	sqrt_d = sqrt(q->disc);
	t[0] = (-q->b - sqrt_d) / (2 * q->a);
	t[1] = (-q->b + sqrt_d) / (2 * q->a);
	check_one_root(best, r, data, t[0]);
	check_one_root(best, r, data, t[1]);
}

static t_perp	calc_perp(t_ray *r, t_cyl_data *data)
{
	t_vec3	oc;
	double	d_dot_a;
	double	oc_dot_a;
	t_perp	result;

	oc = vec3_sub(r->origin, data->cyl->position);
	d_dot_a = vec3_dot(r->direction, data->axis);
	oc_dot_a = vec3_dot(oc, data->axis);
	result.d_perp = vec3_sub(r->direction, vec3_scale(data->axis, d_dot_a));
	result.oc_perp = vec3_sub(oc, vec3_scale(data->axis, oc_dot_a));
	return (result);
}

static void	hit_lateral(t_hit *best, t_ray *r, t_cyl_data *data)
{
	t_perp	perp;
	t_quad	q;

	perp = calc_perp(r, data);
	init_quad(&q, perp.d_perp, perp.oc_perp, data->radius);
	if (fabs(q.a) < 1e-9 || q.disc < 0)
		return ;
	process_lateral_roots(best, r, data, &q);
}

static void	hit_cap(t_hit *best, t_ray *r, t_vec3 center, t_cyl_data *data)
{
	double	denom;
	double	t;
	t_vec3	p;
	t_hit	hit;

	denom = vec3_dot(r->direction, data->axis);
	if (fabs(denom) < 1e-9)
		return ;
	t = vec3_dot(vec3_sub(center, r->origin), data->axis) / denom;
	if (t <= 0)
		return ;
	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	if (vec3_dot(vec3_sub(p, center), vec3_sub(p, center))
		> data->radius * data->radius)
		return ;
	if (denom < 0)
		hit = make_hit_cy(t, p, data->axis, data);
	else
		hit = make_hit_cy(t, p, vec3_scale(data->axis, -1.0), data);
	update_best(best, &hit);
}

t_hit	hit_cylinder(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_cyl_data	data;
	t_hit		best;
	t_vec3		top_center;

	data.cyl = &(geo->cylinder);
	data.axis = vec3_normalize(data.cyl->axis);
	data.radius = data.cyl->diameter * 0.5;
	data.obj = obj;
	best = (t_hit){0};
	hit_lateral(&best, r, &data);
	hit_cap(&best, r, data.cyl->position, &data);
	top_center = vec3_add(data.cyl->position,
			vec3_scale(data.axis, data.cyl->height));
	hit_cap(&best, r, top_center, &data);
	return (best);
}
