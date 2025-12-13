/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:44:57 by dario             #+#    #+#             */
/*   Updated: 2025/12/13 19:45:00 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vector.h"

void	update_best(t_hit *best, t_hit *candidate)
{
	if (candidate->did_hit && (!best->did_hit
			|| candidate->distance < best->distance))
		*best = *candidate;
}
