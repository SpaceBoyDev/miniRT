#include "../../include/render.h"
#include "../../include/vector.h"

static void	hit_paraboloid_surface(t_hit *best, t_pb_ctx *ctx)
{
	t_quad	q;

	q = init_quadratic_pa(ctx);
	if (fabs(q.a) < EPS)
		return ;
	solve_quadratic(best, ctx, &q);
}

static t_vec3	compute_base_normal(double denom, t_pb_ctx *ctx)
{
	t_vec3	n;

	if (denom < 0)
		n = ctx->axis;
	else
		n = vec3_scale(ctx->axis, -1.0);
	if (vec3_dot(n, ctx->r->direction) > 0)
		n = vec3_scale(n, -1.0);
	return (n);
}

static void	check_base_hit(t_hit *best, t_pb_ctx *ctx,
				t_vec3 center, double t)
{
	t_vec3	p;
	t_vec3	v_to_base;
	double	base_r_sq;
	t_hit	h;

	p = vec3_add(ctx->r->origin, vec3_scale(ctx->r->direction, t));
	v_to_base = vec3_sub(p, center);
	base_r_sq = ctx->pb->k_factor * ctx->pb->h_limit;
	if (vec3_dot(v_to_base, v_to_base) <= base_r_sq)
	{
		h = make_paraboloid_hit(ctx, t, p,
				compute_base_normal(vec3_dot(ctx->r->direction, ctx->axis),
					ctx));
		if (h.did_hit && (!best->did_hit || h.distance < best->distance))
			*best = h;
	}
}

static void	hit_paraboloid_base(t_hit *best, t_pb_ctx *ctx)
{
	t_vec3	center;
	double	denom;
	double	t;

	center = vec3_add(ctx->pb->position,
			vec3_scale(ctx->axis, ctx->pb->h_limit));
	denom = vec3_dot(ctx->r->direction, ctx->axis);
	if (fabs(denom) < EPS)
		return ;
	t = vec3_dot(vec3_sub(center, ctx->r->origin), ctx->axis) / denom;
	if (t <= EPS)
		return ;
	check_base_hit(best, ctx, center, t);
}

t_hit	hit_paraboloid(t_obj *obj, t_geo *geo, t_ray *r)
{
	t_pb_ctx	ctx;
	t_hit		best;

	ctx.pb = &(geo->paraboloid);
	ctx.axis = vec3_normalize(ctx.pb->axis);
	ctx.obj = obj;
	ctx.r = r;
	best = (t_hit){0};
	hit_paraboloid_surface(&best, &ctx);
	hit_paraboloid_base(&best, &ctx);
	return (best);
}
