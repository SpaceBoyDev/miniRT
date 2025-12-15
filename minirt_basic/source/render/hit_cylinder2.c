/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:44:44 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:44:45 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

void	init_quad(t_quad *q, t_vec3 d_perp, t_vec3 oc_perp, double r)
{
	q->a = vec3_dot(d_perp, d_perp);
	q->b = 2 * vec3_dot(oc_perp, d_perp);
	q->c = vec3_dot(oc_perp, oc_perp) - r * r;
	q->disc = q->b * q->b - 4 * q->a * q->c;
}

t_hit	make_hit_cy(double t, t_vec3 p, t_vec3 n, t_cyl_data *data)
{
	t_hit	h;

	h = (t_hit){0};
	h.did_hit = 1;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = data->obj;
	h.color = data->cyl->color;
	return (h);
}

t_hit	check_lateral_hit(t_ray *r, double t,
					double height, t_cyl_data *data)
{
	t_hit	h;
	t_vec3	p;
	t_vec3	radial;

	h = (t_hit){0};
	if (height < 0 || height > data->cyl->height || t <= 0)
		return (h);
	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	radial = vec3_sub(vec3_sub(p, data->cyl->position),
			vec3_scale(data->axis, height));
	return (make_hit_cy(t, p, vec3_normalize(radial), data));
}

void	check_one_root(t_hit *best, t_ray *r,
				t_cyl_data *data, double t)
{
	t_vec3	p;
	double	h;
	t_hit	hit;

	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	h = vec3_dot(vec3_sub(p, data->cyl->position), data->axis);
	hit = check_lateral_hit(r, t, h, data);
	update_best(best, &hit);
}
