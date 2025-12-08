/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:43:16 by dario             #+#    #+#             */
/*   Updated: 2025/12/08 21:42:42 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

// void fps_counter(mlx_t *mlx, t_fps *fps) {
//     struct timeval tv;
//     double current_time;
//     int oldest_idx;
//     double delta_total;
//     char str[32];
//     gettimeofday(&tv, NULL);
//     current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
//     fps->frame_times[fps->index] = current_time;
//     fps->index = (fps->index + 1) % 60;
//     if (fps->count < 60)
//         fps->count++;
//     if (fps->count > 5)
//     {
//         if (fps->count < 60)
//             oldest_idx = 0;
//         else
//             oldest_idx = fps->index;
//         delta_total = current_time - fps->frame_times[oldest_idx];
//         fps->current_fps = (fps->count) / delta_total;
//     }
//     if (current_time - fps->last_update > 0.5 && fps->count > 5)
//     {
//         ft_memcpy(str, "Fps: ", 5);
//         ft_dtoa(fps->current_fps, str + 5, 1);
//         mlx_put_string(mlx, str, 10, 10);
//         fps->last_update = current_time;
//     }
// }
