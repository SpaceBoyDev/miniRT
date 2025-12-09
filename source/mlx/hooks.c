/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:14:31 by dario             #+#    #+#             */
/*   Updated: 2025/11/26 00:38:56 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx.h"
#include "../../include/render.h"
#include "../../include/vector.h"
#include <sys/time.h>

void	vec3_translate_by_dir(t_vec3 *pos, t_vec3 dir, \
double speed, bool negative)
{
	float	len;
	float	scale;
	t_vec3	offset;

	len = sqrtf(vec3_magnitude(dir));
	if (len <= 1e-6f)
		return ;
	scale = (float)speed / len;
	offset.x = dir.x * scale;
	offset.y = dir.y * scale;
	offset.z = dir.z * scale;
	if (negative)
	{
		pos->x -= offset.x;
		pos->y -= offset.y;
		pos->z -= offset.z;
	}
	else
	{
		pos->x += offset.x;
		pos->y += offset.y;
		pos->z += offset.z;
	}
}

void	cam_move_forward_back(t_data *data, t_vec3 *pos, \
t_vec3 *ori, const double speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		vec3_translate_by_dir(pos, *ori, speed, false);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		vec3_translate_by_dir(pos, *ori, speed, true);
}

void	cam_move_sideways(t_data *data, t_vec3 *pos, \
t_vec3 right, const double speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		vec3_translate_by_dir(pos, right, speed, false);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		vec3_translate_by_dir(pos, right, speed, true);
}

void	cam_move_vertical(t_data *data, t_vec3 *pos)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		--pos->y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		++pos->y;
}

void	render_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	render(data);
    // fps_counter(data->mlx, data->fps);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
