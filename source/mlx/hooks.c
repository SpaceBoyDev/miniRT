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

void	vec3_translate_by_dir(t_vec3 *pos, t_vec3 dir, double speed, bool negative)
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

void	cam_move_forward_back(t_data *data, t_vec3 *pos, t_vec3 *ori, const double speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		vec3_translate_by_dir(pos, *ori, speed, false);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		vec3_translate_by_dir(pos, *ori, speed, true);
}

void	cam_move_sideways(t_data *data, t_vec3 *pos, t_vec3 right, const double speed)
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

void	move_cam_hook(void *param)
{
	t_data			*data;
	t_vec3			*pos;
	t_vec3			*ori;
	const double	speed = 1.0;
	t_vec3			right;

	data = (t_data *)param;
	pos = &data->scene->camera->position;
	ori = &data->scene->camera->orientation;
	right = vec3_cross(*ori, vec3(0, 1, 0));
	cam_move_forward_back(data, pos, ori, speed);
	cam_move_sideways(data, pos, right, speed);
	cam_move_vertical(data, pos);
}

t_vec3	vec3_rotate_rodrigues(t_vec3 v, t_vec3 k, float angle)
{
	float	cos_a;
	float	sin_a;
	float	dot;
	t_vec3	v_rot;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	dot = v.x * k.x + v.y * k.y + v.z * k.z;
	v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1.0f - cos_a);
	v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1.0f - cos_a);
	v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1.0f - cos_a);
	return (v_rot);
}

void	cam_pitch(t_vec3 *ori, t_vec3 right, const double speed, bool up)
{
	float	angle;
	float	rlen;
	t_vec3	k;
	t_vec3	v_rot;
	float	vlen;

	rlen = sqrtf(vec3_magnitude(right));
	if (rlen <= 1e-6f)
		return ;
	if (up)
		angle = 5.0f * (3.14159265f / 180.0f) * (float)speed;
	else
		angle = -5.0f * (3.14159265f / 180.0f) * (float)speed;
	k = vec3(right.x / rlen, right.y / rlen, right.z / rlen);
	v_rot = vec3_rotate_rodrigues(*ori, k, angle);
	vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
	if (vlen > 1e-6f)
	{
		ori->x = v_rot.x / vlen;
		ori->y = v_rot.y / vlen;
		ori->z = v_rot.z / vlen;
	}
}

void	cam_yaw(t_vec3 *ori, const double speed, bool left)
{
	float	angle;
	t_vec3	k;
	t_vec3	v_rot;
	float	vlen;

	if (left)
		angle = 5.0f * (3.14159265f / 180.0f) * (float)speed;
	else
		angle = -5.0f * (3.14159265f / 180.0f) * (float)speed;
	k = vec3(0, 1, 0); /* Eje Y fijo */
	v_rot = vec3_rotate_rodrigues(*ori, k, angle);
	vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
	if (vlen > 1e-6f)
	{
		ori->x = v_rot.x / vlen;
		ori->y = v_rot.y / vlen;
		ori->z = v_rot.z / vlen;
	}
}

void	look_cam_hook(void *param)
{
	t_data			*data;
	t_vec3			*ori;
	const double	speed = 1.0;
	t_vec3			right;

	data = (t_data *)param;
	ori = &data->scene->camera->orientation;
	right = vec3_cross(*ori, vec3(0, 1, 0));
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		cam_pitch(ori, right, speed, true);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		cam_pitch(ori, right, speed, false);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		cam_yaw(ori, speed, true);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		cam_yaw(ori, speed, false);
}

void	render_hook(void *param)
{
	t_data	*data;
	data = (t_data *)param;

	render(data);
    // fps_counter(data->mlx, data->fps);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
