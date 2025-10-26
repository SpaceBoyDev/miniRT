/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:15:12 by dario             #+#    #+#             */
/*   Updated: 2025/10/26 20:30:46 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include "miniRT.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

// hooks.c
void	close_window_hook(void *param);
void	move_cam_hook(void *param);
void	look_cam_hook(void *param);
void	render_hook(void *param);

// initialization.c
int	initialize_mlx(t_data *data);

#endif