/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:15:12 by dario             #+#    #+#             */
/*   Updated: 2025/12/09 10:22:49 by alepinto         ###   ########.fr       */
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
int		initialize_mlx(t_data *data);

//camera.h
void	cam_yaw(t_vec3 *ori, const double speed, bool left);
void	look_cam_hook(void *param);
void	cam_pitch(t_vec3 *ori, t_vec3 right, const double speed, bool up);
t_vec3	vec3_rotate_rodrigues(t_vec3 v, t_vec3 k, float angle);
void	move_cam_hook(void *param);
void	cam_move_forward_back(t_data *data, t_vec3 *pos, \
t_vec3 *ori, const double speed);
void	cam_move_sideways(t_data *data, t_vec3 *pos, \
t_vec3 right, const double speed);
void	cam_move_vertical(t_data *data, t_vec3 *pos);

#endif
