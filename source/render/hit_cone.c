#include "../../include/render.h"
#include "../../include/vector.h"

s
static t_hit	make_paraboloid_hit(double t, t_vec3 p, t_vec3 n, t_paraboloid *pb, t_obj *obj)
{
	t_hit	h = {0};

	h.did_hit = true;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = obj;
	h.color = pb->color;
	return (h);
}

static void	update_best(t_hit *best, t_hit *candidate)
{
	if (candidate->did_hit && (!best->did_hit
		|| candidate->distance < best->distance))
		*best = *candidate;
}

// La normal del parabolide (Gradiente: 2*X_perp - k_factor*A)
static t_vec3	compute_paraboloid_normal(t_vec3 p, t_paraboloid *pb, t_vec3 axis)
{
	t_vec3	v;
	t_vec3	radial_proj;
	t_vec3	n;
	double	h;

	v = vec3_sub(p, pb->position);
	h = vec3_dot(v, axis);

	radial_proj = vec3_sub(v, vec3_scale(axis, h)); // X_perp (Componente perpendicular)

	// N_raw = 2 * X_perp - k_factor * A (Fórmula del Gradiente)
	n = vec3_sub(vec3_scale(radial_proj, 2.0), vec3_scale(axis, pb->k_factor));

	return (vec3_normalize(n));
}

static void	hit_paraboloid_surface(t_hit *best, t_ray *r, t_paraboloid *pb,
				t_vec3 axis, t_obj *obj)
{
	t_vec3	v = vec3_sub(r->origin, pb->position);
	double	d_dot_a; 
	double	v_dot_a;
	double	a;
	double	b;
	double	c_val;
	double	disc;
	double	t[2];
	double	q; // Variable para la fórmula robusta

	d_dot_a = vec3_dot(r->direction, axis);
	v_dot_a = vec3_dot(v, axis);

	// Ecuación cuadrática r^2 - k*z = 0
	a = vec3_dot(r->direction, r->direction) - pow(d_dot_a, 2);
	
	b = 2.0 * (vec3_dot(v, r->direction) - v_dot_a * d_dot_a) - pb->k_factor * d_dot_a;
	
	c_val = vec3_dot(v, v) - pow(v_dot_a, 2) - pb->k_factor * v_dot_a;

	if (fabs(a) < EPS)
		return ;

	disc = b * b - 4.0 * a * c_val;
	if (disc < 0)
		return ;

	disc = sqrt(disc);
	
	// Uso de la fórmula cuadrática robusta para evitar cancelación sustractiva
	if (b < 0)
		q = -0.5 * (b - disc);
	else
		q = -0.5 * (b + disc);
	
	t[0] = q / a;
	t[1] = c_val / q;

	if (t[0] > t[1]) // Aseguramos que t[0] sea la raíz más pequeña
	{
		double temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}


	for (int i = 0; i < 2; i++)
	{
		if (t[i] <= EPS)
			continue;

		t_vec3	p = vec3_add(r->origin, vec3_scale(r->direction, t[i]));
		double	h = vec3_dot(vec3_sub(p, pb->position), axis);

		if (h < 0.0 || h > pb->h_limit)
			continue;

		t_vec3	n = compute_paraboloid_normal(p, pb, axis);
		
		// Inversión: La normal debe apuntar hacia el rayo de la cámara
		if (vec3_dot(n, r->direction) > 0)
			n = vec3_scale(n, -1.0);
			
		t_hit	hit = make_paraboloid_hit(t[i], p, n, pb, obj);
		update_best(best, &hit);
	}
}

static void	hit_paraboloid_base(t_hit *best, t_ray *r, t_paraboloid *pb,
			t_vec3 axis, t_obj *obj)
{
	t_vec3	center;
	t_vec3	v_to_base;
	double	denom;
	double	t;
	t_vec3	n; // Normal de la base

	center = vec3_add(pb->position, vec3_scale(axis, pb->h_limit));
	denom = vec3_dot(r->direction, axis);

	if (fabs(denom) < EPS)
		return ;

	t = vec3_dot(vec3_sub(center, r->origin), axis) / denom;

	if (t <= EPS)
		return ;

	t_vec3	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	v_to_base = vec3_sub(p, center);

	double	base_r_sq = pb->k_factor * pb->h_limit;
	if (vec3_dot(v_to_base, v_to_base) <= base_r_sq)
	{
		// CORRECCIÓN: La normal de la base siempre debe ser -axis (hacia abajo)
		// y solo se invierte si el rayo viene del interior.
		if (denom < 0)
			n = axis; // El rayo viene del lado positivo, la normal apunta en la dirección de axis
		else
			n = vec3_scale(axis, -1.0); // El rayo viene del lado negativo (base), normal apunta -axis

		// La base es un plano, la normal debe apuntar contra el rayo
		if (vec3_dot(n, r->direction) > 0)
			n = vec3_scale(n, -1.0);
			
		t_hit	h = make_paraboloid_hit(t, p, n, pb, obj);
		update_best(best, &h);
	}
}


t_hit	hit_paraboloid(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_paraboloid	*pb = &(geo->paraboloid);
	t_vec3			axis;
	t_hit			best = {0};

	axis = vec3_normalize(pb->axis);
	hit_paraboloid_surface(&best, r, pb, axis, obj);
	hit_paraboloid_base(&best, r, pb, axis, obj);
	return (best);
}
static t_hit	make_paraboloid_hit(double t, t_vec3 p, t_vec3 n, t_paraboloid *pb, t_obj *obj)
{
	t_hit	h = {0};

	h.did_hit = true;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = obj;
	h.color = pb->color;
	return (h);
}

static void	update_best(t_hit *best, t_hit *candidate)
{
	if (candidate->did_hit && (!best->did_hit
		|| candidate->distance < best->distance))
		*best = *candidate;
}

// La normal del parabolide (Gradiente: 2*X_perp - k_factor*A)
static t_vec3	compute_paraboloid_normal(t_vec3 p, t_paraboloid *pb, t_vec3 axis)
{
	t_vec3	v;
	t_vec3	radial_proj;
	t_vec3	n;
	double	h;

	v = vec3_sub(p, pb->position);
	h = vec3_dot(v, axis);

	radial_proj = vec3_sub(v, vec3_scale(axis, h)); // X_perp (Componente perpendicular)

	// N_raw = 2 * X_perp - k_factor * A (Fórmula del Gradiente)
	n = vec3_sub(vec3_scale(radial_proj, 2.0), vec3_scale(axis, pb->k_factor));

	return (vec3_normalize(n));
}

static void	hit_paraboloid_surface(t_hit *best, t_ray *r, t_paraboloid *pb,
				t_vec3 axis, t_obj *obj)
{
	t_vec3	v = vec3_sub(r->origin, pb->position);
	double	d_dot_a; 
	double	v_dot_a;
	double	a;
	double	b;
	double	c_val;
	double	disc;
	double	t[2];
	double	q; // Variable para la fórmula robusta

	d_dot_a = vec3_dot(r->direction, axis);
	v_dot_a = vec3_dot(v, axis);

	// Ecuación cuadrática r^2 - k*z = 0
	a = vec3_dot(r->direction, r->direction) - pow(d_dot_a, 2);
	
	b = 2.0 * (vec3_dot(v, r->direction) - v_dot_a * d_dot_a) - pb->k_factor * d_dot_a;
	
	c_val = vec3_dot(v, v) - pow(v_dot_a, 2) - pb->k_factor * v_dot_a;

	if (fabs(a) < EPS)
		return ;

	disc = b * b - 4.0 * a * c_val;
	if (disc < 0)
		return ;

	disc = sqrt(disc);
	
	// Uso de la fórmula cuadrática robusta para evitar cancelación sustractiva
	if (b < 0)
		q = -0.5 * (b - disc);
	else
		q = -0.5 * (b + disc);
	
	t[0] = q / a;
	t[1] = c_val / q;

	if (t[0] > t[1]) // Aseguramos que t[0] sea la raíz más pequeña
	{
		double temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}


	for (int i = 0; i < 2; i++)
	{
		if (t[i] <= EPS)
			continue;

		t_vec3	p = vec3_add(r->origin, vec3_scale(r->direction, t[i]));
		double	h = vec3_dot(vec3_sub(p, pb->position), axis);

		if (h < 0.0 || h > pb->h_limit)
			continue;

		t_vec3	n = compute_paraboloid_normal(p, pb, axis);
		
		// Inversión: La normal debe apuntar hacia el rayo de la cámara
		if (vec3_dot(n, r->direction) > 0)
			n = vec3_scale(n, -1.0);
			
		t_hit	hit = make_paraboloid_hit(t[i], p, n, pb, obj);
		update_best(best, &hit);
	}
}

static void	hit_paraboloid_base(t_hit *best, t_ray *r, t_paraboloid *pb,
			t_vec3 axis, t_obj *obj)
{
	t_vec3	center;
	t_vec3	v_to_base;
	double	denom;
	double	t;
	t_vec3	n; // Normal de la base

	center = vec3_add(pb->position, vec3_scale(axis, pb->h_limit));
	denom = vec3_dot(r->direction, axis);

	if (fabs(denom) < EPS)
		return ;

	t = vec3_dot(vec3_sub(center, r->origin), axis) / denom;

	if (t <= EPS)
		return ;

	t_vec3	p = vec3_add(r->origin, vec3_scale(r->direction, t));
	v_to_base = vec3_sub(p, center);

	double	base_r_sq = pb->k_factor * pb->h_limit;
	if (vec3_dot(v_to_base, v_to_base) <= base_r_sq)
	{
		// CORRECCIÓN: La normal de la base siempre debe ser -axis (hacia abajo)
		// y solo se invierte si el rayo viene del interior.
		if (denom < 0)
			n = axis; // El rayo viene del lado positivo, la normal apunta en la dirección de axis
		else
			n = vec3_scale(axis, -1.0); // El rayo viene del lado negativo (base), normal apunta -axis

		// La base es un plano, la normal debe apuntar contra el rayo
		if (vec3_dot(n, r->direction) > 0)
			n = vec3_scale(n, -1.0);
			
		t_hit	h = make_paraboloid_hit(t, p, n, pb, obj);
		update_best(best, &h);
	}
}


t_hit	hit_paraboloid(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_paraboloid	*pb = &(geo->paraboloid);
	t_vec3			axis;
	t_hit			best = {0};

	axis = vec3_normalize(pb->axis);
	hit_paraboloid_surface(&best, r, pb, axis, obj);
	hit_paraboloid_base(&best, r, pb, axis, obj);
	return (best);
}tatic t_hit	make_cone_hit(double t, t_vec3 p, t_vec3 n, t_cone *c, t_obj *obj)
{
	t_hit	h = {0};

	h.did_hit = true;
	h.distance = t;
	h.hit_point = p;
	h.normal = n;
	h.hit_obj = obj;
	h.color = c->color;
	return (h);
}

static void	update_best(t_hit *best, t_hit *candidate)
{
	if (candidate->did_hit && (!best->did_hit
		|| candidate->distance < best->distance))
		*best = *candidate;
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
	k = (c->height * c->height) / (pow(c->diameter / 2.0, 2) + c->height * c->height);
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
