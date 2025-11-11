/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:12 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 20:43:59 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"
# include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// raytrace.c
t_ray	generate_ray(t_camera *cam, int x, int y, int width, int height);
t_color	trace_ray(t_ray *ray, t_scene *scene);

// render_sphere.c
t_sphere	*check_spheres(t_ray *ray, t_hit *ray_hit, t_scene *scene);
t_hit	    hit_plane(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	    hit_sphere(t_obj *obj, t_geo *geo, t_ray *r);
t_hit	hit_cylinder(t_obj *obj, t_geo *geo, t_ray *r);

// render_utils.c
uint32_t	rgb_to_uint(t_color *color);
t_hit (*set_hit_array_func(void))[3];

// render.c
int	render(t_data *data);

#endif