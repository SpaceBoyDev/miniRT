/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:46:01 by dario             #+#    #+#             */
/*   Updated: 2025/10/25 19:06:52 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

int	render(t_data *data)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color;

	color = 475983279;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			mlx_put_pixel(data->img, i, j, color);
			++j;
		}
		++i;
	}

	return (OK);
}