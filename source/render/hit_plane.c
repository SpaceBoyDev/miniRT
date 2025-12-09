#include "../../include/render.h"
#include "../../include/vector.h"

static t_vec3	get_plane_normal(t_plane *p, t_ray *r)
{
	t_vec3	normal;

	if (vec3_dot(r->direction, p->normal) < 0)
		normal = p->normal;
	else
		normal = vec3_scale(p->normal, -1.0);
	return (normal);
}

t_hit	hit_plane(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hit		hit;
	t_plane		*p;
	double		denominator;
	double		dst;

	p = &(geo->plane);
	hit.did_hit = false;
	denominator = vec3_dot(r->direction, p->normal);
	(void)obj;
	if (fabs(denominator) < 1e-6)
		return ((t_hit){0});
	dst = vec3_dot(vec3_sub(p->position, r->origin), p->normal) / denominator;
	if (dst < 1e-6)
		return ((t_hit){0});
	hit.did_hit = true;
	hit.distance = dst;
	hit.hit_point = vec3_add(r->origin, vec3_scale(r->direction, dst));
	hit.normal = get_plane_normal(p, r);
	hit.color = p->color;
	hit.hit_obj = obj;
	return (hit);
}
