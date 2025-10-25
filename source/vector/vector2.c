/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:27:18 by dario             #+#    #+#             */
/*   Updated: 2025/10/25 21:02:39 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

double	vec3_magnitude(t_vec3 vec3)
{
	return (sqrt(pow(vec3.x, 2) + pow(vec3.y, 2) + pow(vec3.z, 2)));
}

t_vec3	vec3_normalize(t_vec3 v3)
{
	return (vec3_scale(v3, 1 / vec3_magnitude(v3)));
}
