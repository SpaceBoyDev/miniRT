/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:12 by dario             #+#    #+#             */
/*   Updated: 2025/12/09 10:23:52 by alepinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"
# include <math.h>
# include <sys/time.h>
# include "structs.h"

// fps_counter.c
int		ft_dtoa(double n, char *str, int precision);
void	fps_counter(mlx_t *mlx, t_fps *fps);

// hit.c
t_hit	hit_plane(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	hit_sphere(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	hit_cylinder(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	hit_cone(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	hit_paraboloid(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	hit_hyperboloid(t_obj *obj, t_geo *geo, t_ray *r);

void	init_quad(t_quad *q, t_vec3 d_perp, t_vec3 oc_perp, double r);
t_hit	make_hit_cy(double t, t_vec3 p, t_vec3 n, t_cyl_data *data);
void	update_best(t_hit *best, t_hit *candidate);
t_hit	check_lateral_hit(t_ray *r, double t, double height, t_cyl_data *data);
void	check_one_root(t_hit *best, t_ray *r, t_cyl_data *data, double t);
t_hit	make_paraboloid_hit(t_pb_ctx *ctx, double t, t_vec3 p, t_vec3 n);
void	solve_quadratic(t_hit *best, t_pb_ctx *ctx, t_quad *q);
t_quad	init_quadratic_pa(t_pb_ctx *ctx);

// light.c
t_color	light_bounce(t_hit *hit, t_scene *scene);

// raytrace.c
t_ray	generate_ray(t_camera *cam, int x, int y);
t_obj	*get_closest_obj(t_ray *ray, t_scene *scene, t_hit *out_hit);
t_color	trace_ray(t_ray *ray, t_scene *scene);

// render_utils.c
void	clear_hit(t_hit *hit);
uint32_t	rgb_to_uint(t_color *color);

// render.c
int		render(t_data *data);

#endif