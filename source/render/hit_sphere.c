#include "../../include/render.h"
#include "../../include/vector.h"

t_hit	hit_sphere(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_sphere *s = &(geo->sphere);
	t_hit	hit;
	t_vec3	offset;
	double	a;
	double	b; 
	double	c;
	double	discriminant;
	double	dst;
	clear_hit(&hit);

	offset = vec3_sub(r->origin, s->position);
	a = vec3_dot(r->direction, r->direction);
	b = 2 * vec3_dot(offset, r->direction);
	c = vec3_dot(offset, offset) - pow(s->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		dst = (-b - sqrt(discriminant)) / (2.0 * a);
		if (dst >= 0)
		{
			hit.did_hit = true;
			hit.distance = dst;
			hit.hit_point = vec3_add(r->origin, vec3_scale(r->direction, dst));
			hit.normal = vec3_normalize(vec3_sub(hit.hit_point, s->position));
			if (vec3_dot(hit.normal, r->direction) > 0)
				hit.normal = vec3_scale(hit.normal, -1.0);
			hit.hit_obj = obj;
			hit.color = s->color;
		}
	}
	return (hit);
}
