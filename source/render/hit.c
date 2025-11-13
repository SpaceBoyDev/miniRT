/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:25 by dario             #+#    #+#             */
/*   Updated: 2025/11/13 17:26:50 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void	clear_hit(t_hit *hit)
{
	hit->color = (t_color){0, 0, 0};
	hit->did_hit = false;
	hit->distance = 0;
	hit->hit_obj = NULL;
	hit->hit_point = (t_vec3) {0, 0, 0};
	hit->normal = (t_vec3) {0, 0, 0};
}