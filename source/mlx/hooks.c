/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:14:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/25 20:00:45 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx.h"
#include "../../include/render.h"

void	close_window_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		// mlx_terminate(mlx); COMENTADO POR AHORA PORQUE CAUSA SEGFAULT ??
	}
}

void	render_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	render(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	
}
