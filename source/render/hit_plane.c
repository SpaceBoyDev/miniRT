#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	hit_plane(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hit	hit = {0};
	t_plane	*p = &(geo->plane);
	double	denominator = vec3_dot(r->direction, p->normal);
	(void)obj;
	if (fabs(denominator) < __DBL_EPSILON__)
		return hit;

	double	dst = vec3_dot(vec3_sub(p->position, r->origin), p->normal) / denominator;
	if (dst < 0)
		return hit;

	hit.did_hit = true;
	hit.distance = dst;
	hit.hit_point = vec3_add(r->origin, vec3_scale(r->direction, dst));
	if (vec3_dot(r->direction, p->normal) < 0)
		hit.normal = p->normal;
	else
		hit.normal = vec3_scale(p->normal, -1);
    hit.color = p->color;

	return hit;
}
