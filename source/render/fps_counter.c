#include "../../include/render.h"

void	calculate_and_render_fps(mlx_t *mlx, t_fps *fps)
{
	double	current_time;
	int		oldest_idx;
	double	delta_total;
	char	str[32];

	current_time = fps->frame_times[(fps->index - 1 + 60) % 60];
	if (fps->count > 5)
	{
		if (fps->count < 60)
			oldest_idx = 0;
		else
			oldest_idx = fps->index;
		delta_total = current_time - fps->frame_times[oldest_idx];
		fps->current_fps = (fps->count) / delta_total;
	}
	if (current_time - fps->last_update > 0.5 && fps->count > 5)
	{
		ft_memcpy(str, "Fps: ", 5);
		ft_dtoa(fps->current_fps, str + 5, 1);
		mlx_put_string(mlx, str, 10, 10);
		fps->last_update = current_time;
	}
}

void	fps_counter(mlx_t *mlx, t_fps *fps)
{
	struct timeval	tv;
	double			current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	fps->frame_times[fps->index] = current_time;
	fps->index = (fps->index + 1) % 60;
	if (fps->count < 60)
		fps->count++;
	calculate_and_render_fps(mlx, fps);
}
