/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 22:14:31 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 20:05:10 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx.h"
#include "../../include/render.h"
#include "../../include/vector.h"

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

void	move_cam_hook(void *param)
{
	t_data	*data;
	t_vec3 *pos;
	t_vec3 *ori;
	const double speed = 1;
	t_vec3	right;

	data = (t_data *)param;
	pos = &data->scene->camera->position;
	ori = &data->scene->camera->orientation;
	right = vec3_cross(*ori, vec3(0, 1, 0));
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		float len = sqrtf(vec3_magnitude(*ori));
		if (len <= 1e-6f)
			return;
		pos->x -= (ori->x / len) * speed;
		pos->y -= (ori->y / len) * speed;
		pos->z -= (ori->z / len) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		float len = sqrtf(vec3_magnitude(*ori));
		if (len <= 1e-6f)
			return;
		pos->x += (ori->x / len) * speed;
		pos->y += (ori->y / len) * speed;
		pos->z += (ori->z / len) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		float rlen = sqrtf(vec3_magnitude(right));
		if (rlen <= 1e-6f)
			return;
		pos->x += (right.x / rlen) * speed;
		pos->y += (right.y / rlen) * speed;
		pos->z += (right.z / rlen) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		float rlen = sqrtf(vec3_magnitude(right));
		if (rlen <= 1e-6f)
			return;
		pos->x -= (right.x / rlen) * speed;
		pos->y -= (right.y / rlen) * speed;
		pos->z -= (right.z / rlen) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
	{
		--pos->y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
	{
		++pos->y;
	}
}

void	look_cam_hook(void *param)
{
	t_data	*data;
	t_vec3 *ori;
	const double speed = 1;
	t_vec3	right;

	data = (t_data *)param;
	ori = &data->scene->camera->orientation;
	right = vec3_cross(*ori, vec3(0, 1, 0));
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		float rlen = sqrtf(vec3_magnitude(right));
		if (rlen <= 1e-6f)
			return;
		/* ángulo pequeño en radianes (ej. 5 grados * speed) */
		float angle = 5.0f * (3.14159265f / 180.0f) * (float)speed;
		t_vec3 v = *ori;
		t_vec3 k = vec3(right.x / rlen, right.y / rlen, right.z / rlen);
		float cos_a = cosf(angle);
		float sin_a = sinf(angle);
		float dot = v.x * k.x + v.y * k.y + v.z * k.z;
		t_vec3 v_rot;
		v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1 - cos_a);
		v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1 - cos_a);
		v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1 - cos_a);
		/* normalizar la orientación resultante */
		float vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
		if (vlen > 1e-6f)
		{
			ori->x = v_rot.x / vlen;
			ori->y = v_rot.y / vlen;
			ori->z = v_rot.z / vlen;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		float rlen = sqrtf(vec3_magnitude(right));
		if (rlen <= 1e-6f)
			return;
		/* ángulo pequeño en radianes (ej. -5 grados * speed) para mirar hacia abajo */
		float angle = -5.0f * (3.14159265f / 180.0f) * (float)speed;
		t_vec3 v = *ori;
		t_vec3 k = vec3(right.x / rlen, right.y / rlen, right.z / rlen);
		float cos_a = cosf(angle);
		float sin_a = sinf(angle);
		float dot = v.x * k.x + v.y * k.y + v.z * k.z;
		t_vec3 v_rot;
		v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1 - cos_a);
		v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1 - cos_a);
		v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1 - cos_a);
		/* normalizar la orientación resultante */
		float vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
		if (vlen > 1e-6f)
		{
			ori->x = v_rot.x / vlen;
			ori->y = v_rot.y / vlen;
			ori->z = v_rot.z / vlen;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		float rlen = sqrtf(vec3_magnitude(right));
		if (rlen <= 1e-6f)
			return;
		/* ángulo pequeño en radianes (ej. -5 grados * speed) para mirar hacia abajo */
		float angle = -5.0f * (3.14159265f / 180.0f) * (float)speed;
		t_vec3 v = *ori;
		t_vec3 k = vec3(right.x / rlen, right.y / rlen, right.z / rlen);
		float cos_a = cosf(angle);
		float sin_a = sinf(angle);
		float dot = v.x * k.x + v.y * k.y + v.z * k.z;
		t_vec3 v_rot;
		v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1 - cos_a);
		v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1 - cos_a);
		v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1 - cos_a);
		/* normalizar la orientación resultante */
		float vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
		if (vlen > 1e-6f)
		{
			/* girar alrededor del eje up (0,1,0) para mirar a la izquierda */
			float angle = 5.0f * (3.14159265f / 180.0f) * (float)speed;
			t_vec3 v = *ori;
			t_vec3 k = vec3(0, 1, 0); /* ya unitario */
			float cos_a = cosf(angle);
			float sin_a = sinf(angle);
			float dot = v.x * k.x + v.y * k.y + v.z * k.z;
			t_vec3 v_rot;
			v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1 - cos_a);
			v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1 - cos_a);
			v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1 - cos_a);
			/* normalizar la orientación resultante */
			float vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
			if (vlen > 1e-6f)
			{
				ori->x = v_rot.x / vlen;
				ori->y = v_rot.y / vlen;
				ori->z = v_rot.z / vlen;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		float rlen = sqrtf(vec3_magnitude(right));
		if (rlen <= 1e-6f)
			return;
		/* ángulo pequeño en radianes (ej. -5 grados * speed) para mirar hacia abajo */
		float angle = -5.0f * (3.14159265f / 180.0f) * (float)speed;
		t_vec3 v = *ori;
		t_vec3 k = vec3(right.x / rlen, right.y / rlen, right.z / rlen);
		float cos_a = cosf(angle);
		float sin_a = sinf(angle);
		float dot = v.x * k.x + v.y * k.y + v.z * k.z;
		t_vec3 v_rot;
		v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1 - cos_a);
		v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1 - cos_a);
		v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1 - cos_a);
		/* normalizar la orientación resultante */
		float vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
		if (vlen > 1e-6f)
		{
			/* girar alrededor del eje up (0,1,0) para mirar a la izquierda */
			float angle = -5.0f * (3.14159265f / 180.0f) * (float)speed;
			t_vec3 v = *ori;
			t_vec3 k = vec3(0, 1, 0); /* ya unitario */
			float cos_a = cosf(angle);
			float sin_a = sinf(angle);
			float dot = v.x * k.x + v.y * k.y + v.z * k.z;
			t_vec3 v_rot;
			v_rot.x = v.x * cos_a + (k.y * v.z - k.z * v.y) * sin_a + k.x * dot * (1 - cos_a);
			v_rot.y = v.y * cos_a + (k.z * v.x - k.x * v.z) * sin_a + k.y * dot * (1 - cos_a);
			v_rot.z = v.z * cos_a + (k.x * v.y - k.y * v.x) * sin_a + k.z * dot * (1 - cos_a);
			/* normalizar la orientación resultante */
			float vlen = sqrtf(v_rot.x * v_rot.x + v_rot.y * v_rot.y + v_rot.z * v_rot.z);
			if (vlen > 1e-6f)
			{
				ori->x = v_rot.x / vlen;
				ori->y = v_rot.y / vlen;
				ori->z = v_rot.z / vlen;
			}
		}
	}
}

void	render_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	render(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
