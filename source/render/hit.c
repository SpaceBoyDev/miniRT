/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:28:21 by dario             #+#    #+#             */
/*   Updated: 2025/11/25 21:34:38 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_hit	hit_plane(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_hit	hit = {0}; // Inicializa todos los campos a cero
	t_plane	*p = &(geo->plane);
	double	denominator = vec3_dot(r->direction, p->normal);
	(void)obj;
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

t_hit hit_cylinder(t_obj *obj, t_geo *geo, t_ray *r)
{
    t_cylinder *c = &(geo->cylinder);
    t_hit best = {0};

    double radius = c->diameter * 0.5;
    t_vec3 axis = vec3_normalize(c->axis);
    t_vec3 oc = vec3_sub(r->origin, c->position);

    /* =======================================================
    ** 1) INTERSECCIÓN LATERAL DEL CILINDRO
    ** ======================================================= */

    double d_dot_a  = vec3_dot(r->direction, axis);
    double oc_dot_a = vec3_dot(oc, axis);

    t_vec3 d_perp  = vec3_sub(r->direction, vec3_scale(axis, d_dot_a));
    t_vec3 oc_perp = vec3_sub(oc, vec3_scale(axis, oc_dot_a));

    double a = vec3_dot(d_perp, d_perp);
    double b = 2 * vec3_dot(oc_perp, d_perp);
    double c_val = vec3_dot(oc_perp, oc_perp) - radius * radius;

    double disc = b*b - 4*a*c_val;

    if (fabs(a) > 1e-9 && disc >= 0)
    {
        double sqrtD = sqrt(disc);
        double t0 = (-b - sqrtD) / (2*a);
        double t1 = (-b + sqrtD) / (2*a);

        for (int i = 0; i < 2; i++)
        {
            double t = (i == 0 ? t0 : t1);
            if (t <= 0) continue;

            t_vec3 p = vec3_add(r->origin, vec3_scale(r->direction, t));

            double h = vec3_dot(vec3_sub(p, c->position), axis);

            if (h >= 0 && h <= c->height)
            {
                t_hit h_hit = {0};
                h_hit.did_hit = true;
                h_hit.distance = t;
                h_hit.hit_point = p;

                t_vec3 radial = vec3_sub(vec3_sub(p, c->position), vec3_scale(axis, h));
                h_hit.normal = vec3_normalize(radial);

                h_hit.hit_obj = obj;
                h_hit.color = c->color;

                if (!best.did_hit || t < best.distance)
                    best = h_hit;
            }
        }
    }


    /* =======================================================
    ** 2) INTERSECCIÓN TAPA INFERIOR
    ** ======================================================= */
    {
        t_vec3 center_bot = c->position;
        double denom = vec3_dot(r->direction, axis);

        if (fabs(denom) > 1e-9)
        {
            double t = vec3_dot(vec3_sub(center_bot, r->origin), axis) / denom;
            if (t > 0)
            {
                t_vec3 p = vec3_add(r->origin, vec3_scale(r->direction, t));
                t_vec3 diff = vec3_sub(p, center_bot);
                double dist2 = vec3_dot(diff, diff);

                if (dist2 <= radius * radius)
                {
                    t_hit h_hit = {0};
                    h_hit.did_hit = true;
                    h_hit.distance = t;
                    h_hit.hit_point = p;
                    h_hit.normal = vec3_scale(axis, -1);
                    h_hit.hit_obj = obj;
                    h_hit.color = c->color;

                    if (!best.did_hit || t < best.distance)
                        best = h_hit;
                }
            }
        }
    }


    /* =======================================================
    ** 3) INTERSECCIÓN TAPA SUPERIOR
    ** ======================================================= */
    {
        t_vec3 center_top = vec3_add(c->position, vec3_scale(axis, c->height));
        double denom = vec3_dot(r->direction, axis);

        if (fabs(denom) > 1e-9)
        {
            double t = vec3_dot(vec3_sub(center_top, r->origin), axis) / denom;
            if (t > 0)
            {
                t_vec3 p = vec3_add(r->origin, vec3_scale(r->direction, t));
                t_vec3 diff = vec3_sub(p, center_top);
                double dist2 = vec3_dot(diff, diff);

                if (dist2 <= radius * radius)
                {
                    t_hit h_hit = {0};
                    h_hit.did_hit = true;
                    h_hit.distance = t;
                    h_hit.hit_point = p;
                    h_hit.normal = axis;
                    h_hit.hit_obj = obj;
                    h_hit.color = c->color;

                    if (!best.did_hit || t < best.distance)
                        best = h_hit;
                }
            }
        }
    }

    return best;
}