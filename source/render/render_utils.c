/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:09:56 by dario             #+#    #+#             */
/*   Updated: 2025/10/27 21:00:05 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

uint32_t	rgb_to_uint(t_color *color)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | 255);
}

void fps_counter(mlx_t *mlx, t_fps *fps) {
    struct timeval tv;
    double current_time;
    int oldest_idx;
    double delta_total;
    char str[32];

    gettimeofday(&tv, NULL);
    current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
    
    fps->frame_times[fps->index] = current_time;
    fps->index = (fps->index + 1) % 60;
    if (fps->count < 60)
        fps->count++;
    
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
        printf("FPS: %.1f\n", fps->current_fps);
        fps->last_update = current_time;
    }
}

int ft_dtoa(double n, char *str, int precision)
{
    int i = 0;
    long int_part;
    double frac_part;
    char temp[20]; 
    int digit;

    if (n < 0) {
        str[i++] = '-';
        n = -n;
    }
    
    int_part = (long)n;
    frac_part = n - int_part;
    
    if (int_part == 0)
        str[i++] = '0';
    else {
        
        int j = 0;
        while (int_part > 0) {
            temp[j++] = (int_part % 10) + '0';
            int_part /= 10;
        }
        while (j > 0)
            str[i++] = temp[--j];
    }
    
    if (precision > 0) {
        str[i++] = '.';
        while (precision-- > 0) {
            frac_part *= 10;
            digit = (int)frac_part;
            str[i++] = digit + '0';
            frac_part -= digit;
        }
    }
    
    str[i] = '\0';
    return i;
}
