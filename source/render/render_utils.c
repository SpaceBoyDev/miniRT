/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:09:56 by dario             #+#    #+#             */
/*   Updated: 2025/11/26 16:27:04 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

uint32_t	rgb_to_uint(t_color *color)
{
	int	red;
	int	green;
	int	blue;

	red = color->r * 255;
	green = color->g * 255;
	blue = color->b * 255;
	return (red << 24 | green << 16 | blue << 8 | 255);
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

void	clear_hit(t_hit *hit)
{
	ft_memset(hit, 0, sizeof(t_hit));
	hit->distance = -1;
}
