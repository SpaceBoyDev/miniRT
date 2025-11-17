#include "../../include/render.h"
#include "../../include/vector.h"

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

	offset = vec3_add(r->origin, s->position);
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
			hit.hit_point = vec3_scale(vec3_add(r->origin, r->direction), dst);
			hit.normal = vec3_normalize(vec3_sub(hit.hit_point, s->position));
			hit.hit_obj = obj;
			hit.color = s->color;
		}
	}
	return (hit);
}

t_hit	hit_plane(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hit	hit = {0}; // Inicializa todos los campos a cero
	t_plane	*p = &(geo->plane);
	double	denominator = vec3_dot(r->direction, p->normal);

	if (fabs(denominator) < __DBL_EPSILON__)
		return hit; // Ray is parallel to plane

	double	dst = vec3_dot(vec3_sub(p->position, r->origin), p->normal) / denominator;
	if (dst < 0)
		return hit; // Plane is behind ray

	hit.did_hit = true;
	hit.distance = dst;
	// Calcula el punto de intersección
	hit.hit_point = vec3_add(r->origin, vec3_scale(r->direction, dst));
	// Normal siempre hacia el lado opuesto al ray
	if (vec3_dot(r->direction, p->normal) < 0)
		hit.normal = p->normal;
	else
		hit.normal = vec3_scale(p->normal, -1);

	return hit;
}

t_hit	hit_cylinder(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_cylinder *c = &(geo->cylinder);
	t_hit hit = {0};
	t_vec3 oc = vec3_sub(r->origin, c->position);
	t_vec3 axis = vec3_normalize(c->axis);
	
	// Proyecciones para ecuación cuadrática del cuerpo
	t_vec3 d_perp = vec3_sub(r->direction, vec3_scale(axis, vec3_dot(r->direction, axis)));
	t_vec3 oc_perp = vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis)));
	
	double a = vec3_dot(d_perp, d_perp);
	double b = 2 * vec3_dot(oc_perp, d_perp);
	double c_val = vec3_dot(oc_perp, oc_perp) - pow(c->diameter / 2, 2);
	double discriminant = b * b - 4 * a * c_val;
	
	if (discriminant < 0)
		return (hit);
	
	double t = (-b - sqrt(discriminant)) / (2 * a);
	if (t < 0)
		t = (-b + sqrt(discriminant)) / (2 * a);
	if (t < 0)
		return (hit);
	
	// Verificar altura
	t_vec3 p = vec3_add(r->origin, vec3_scale(r->direction, t));
	double h = vec3_dot(vec3_sub(p, c->position), axis);
	if (h < 0 || h > c->height)
		return (hit);
	
	hit.did_hit = true;
	hit.distance = t;
	hit.hit_point = p;
	hit.normal = vec3_normalize(vec3_sub(vec3_sub(p, c->position), vec3_scale(axis, h)));
	hit.hit_obj = obj;
	hit.color = c->color;
	return (hit);
}


