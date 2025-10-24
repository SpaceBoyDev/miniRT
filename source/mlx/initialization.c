/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:17:45 by dario             #+#    #+#             */
/*   Updated: 2025/10/24 22:27:30 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx.h"
#include "../../include/miniRT.h"

int	initialize_mlx(t_data *data)
{
	data->mlx =  mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, false);
	if (!data->mlx)
		return (ERR_MLX_INIT);
	if (!mlx_loop_hook(data->mlx, &close_window_hook, data->mlx))
		return (ERR_MLX_HOOK);
	mlx_loop(data->mlx);
	return (OK);
}