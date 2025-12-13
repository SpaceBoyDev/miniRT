/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:27:18 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 18:10:39 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

// Crear un vector3
t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

// Suma de vectores. a + b
t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

// Resta de dos vectores. a - b
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

// Multiplicación de un double a un vector. a * b
t_vec3	vec3_scale(t_vec3 v3, double scale)
{
	return (vec3(v3.x * scale, v3.y * scale, v3.z * scale));
}

// División de un double a un vector. a * b
t_vec3	vec3_div(t_vec3 v3, double scale)
{
	return (vec3(v3.x / scale, v3.y / scale, v3.z / scale));
}
