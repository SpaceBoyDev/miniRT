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

#include <sys/time.h>

void fps_counter(struct timeval *start) {
    struct timeval end;
    long elapsed_time;
    static int frame_count = 0;

    gettimeofday(&end, NULL);

    // Calcula el tiempo transcurrido entre 'start' y 'end' en microsegundos
    elapsed_time = (end.tv_sec - start->tv_sec) * 1000000 + (end.tv_usec - start->tv_usec);

    frame_count++;

    if (frame_count >= 60) {
        printf("FPS: %.2f\n", 1000000.0 / (double)elapsed_time);  // Calcula y muestra FPS
        frame_count = 0;  // Reinicia el contador de fotogramas
        *start = end;  // Reemplaza el valor de start con el valor actual de end
    }
}

