/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:14:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/25 01:03:46 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx.h"

void	close_window_hook(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		// mlx_terminate(mlx); COMENTADO POR AHORA PORQUE CAUSA SEGFAULT ??
	}
}